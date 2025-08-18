#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>
#include <pthread.h>
#include "MQTTClient.h"

#define BROKER_ADDRESS "tcp://iot-06z00ak627vyl6x.mqtt.iothub.aliyuncs.com:1883"
#define CLIENTID "k0ay8rGo7wa.device1|securemode=2,signmethod=hmacsha256,timestamp=1755069392663|"
#define USERNAME "device1&k0ay8rGo7wa"
#define PASSWORD "59e214f23338162c6b19d10ad3ba15aae05e4c3a0d176dde398f0aabf85401b0"

#define WILL_TOPIC "/k0ay8rGo7wa/device1/user/will"
#define LED_TOPIC "/k0ay8rGo7wa/device1/user/led"
#define TEMP_TOPIC "/k0ay8rGo7wa/device1/user/temp"
#define ATTR_REPORT_SUB_TPOIC "/sys/k0ay8rGo7wa/device1/thing/event/property/post_reply"
#define ATTR_REPORT_TOPIC "/sys/k0ay8rGo7wa/device1/thing/event/property/post"
#define ATTR_SET_SUB_TOPIC "/sys/k0ay8rGo7wa/device1/thing/service/property/set"

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} CPUStats;

MQTTClient client;
int rc;

// 从 /proc/stat 读取 CPU 时间
int read_cpu_stats(CPUStats *stats) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return -1;
    char buf[256];
    if (fgets(buf, sizeof(buf), fp) == NULL) {
        fclose(fp);
        return -1;
    }
    sscanf(buf, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu",
           &stats->user, &stats->nice, &stats->system, &stats->idle,
           &stats->iowait, &stats->irq, &stats->softirq, &stats->steal);
    fclose(fp);
    return 0;
}

// 计算 CPU 使用率
float calc_cpu_usage(CPUStats *prev, CPUStats *curr) {
    unsigned long long prev_idle = prev->idle + prev->iowait;
    unsigned long long curr_idle = curr->idle + curr->iowait;
    unsigned long long prev_total = prev->user + prev->nice + prev->system + prev->idle +
                                    prev->iowait + prev->irq + prev->softirq + prev->steal;
    unsigned long long curr_total = curr->user + curr->nice + curr->system + curr->idle +
                                    curr->iowait + curr->irq + curr->softirq + curr->steal;
    unsigned long long total_diff = curr_total - prev_total;
    unsigned long long idle_diff = curr_idle - prev_idle;
    if (total_diff == 0) return 0.0;
    return (float)(total_diff - idle_diff) / total_diff * 100.0;
}

static int led_json_parse(char* json_str){
    cJSON* root = cJSON_Parse(json_str);
    if(!root){
        printf("JSON parse error: %s\n", cJSON_GetErrorPtr());
        return -1;
    }
    cJSON* params = cJSON_GetObjectItem(root, "params");
    if(!cJSON_IsObject(params)){
        printf("params is not an object\n");
        cJSON_Delete(root);
        return -1;
    }
    cJSON* led_status = cJSON_GetObjectItem(params, "ledswitch");
    if(!cJSON_IsNumber(led_status)){
        printf("ledswitch is not a number\n");
        cJSON_Delete(root);
        return -1;
    }
    printf("ledswitch: %d\n", led_status->valueint);
    int ret = led_status->valueint;
    cJSON_Delete(root);
    return ret;
}

// 读取 CPU 温度，返回摄氏度
float get_cpu_temp(void) {
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!fp) {
        perror("Failed to open CPU temp file");
        return -1.0f;
    }
    int temp_milli = 0;
    if (fscanf(fp, "%d", &temp_milli) != 1) {
        perror("Failed to read CPU temp");
        fclose(fp);
        return -1.0f;
    }
    fclose(fp);
    return temp_milli / 1000.0f;
}

// 拼接温度和CPU使用率的物模型属性上报 JSON
void build_system_report(char* buf, size_t buf_size, float temperature, float cpu_usage) {
    if (!buf) return;
    long long ts = (long long)time(NULL);
    snprintf(buf, buf_size,
        "{"
            "\"id\":\"%lld\","
            "\"version\":\"1.0.0\","
            "\"method\":\"thing.event.property.post\","
            "\"params\":{"
                "\"CpuTemperature\":%.2f,"
                "\"CpuUsage\":%.2f"
            "}"
        "}",
        ts,
        temperature,
        cpu_usage
    );
}

//cpu状态线程
void* cpu_status_thread(void* arg){
    CPUStats prev_stats, curr_stats;
    char temp_payload[128] = {0};
    float usage = 0.0f, temp = 0.0f;
    MQTTClient_message cpumsg = MQTTClient_message_initializer;
    if (read_cpu_stats(&prev_stats) != 0) {
        perror("Failed to read CPU stats");
        return NULL;
    }
    cpumsg.qos = 0;
    cpumsg.retained = 1;
    while (1) {
        sleep(1);
        if (read_cpu_stats(&curr_stats) != 0) {
            perror("Failed to read CPU stats");
            return NULL;
        }
        usage = calc_cpu_usage(&prev_stats, &curr_stats);
        prev_stats = curr_stats;
        temp = get_cpu_temp();
        build_system_report(temp_payload, sizeof(temp_payload), temp, usage);
        cpumsg.payload = temp_payload;
        cpumsg.payloadlen = strlen(temp_payload);
        if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_publishMessage(client, ATTR_REPORT_TOPIC, &cpumsg, NULL))){
            printf("Failed to publish system report message, return code %d\n", rc);
            rc = EXIT_FAILURE;
            return NULL;
        }
        printf("Published system report: %s\n", temp_payload);
    }
    return NULL;
}

static int msgarrvd(void* conttext, char* topicName, int topicLen, MQTTClient_message* message){
    printf("Message arrived on topic %s:", topicName);
    // printf("Message: %.*s\n", message->payloadlen, (char*)message->payload);
    //led控制
    if(!strcmp(topicName, LED_TOPIC)){
        if(!strcmp("2", message->payload)){
            system("echo heartbeat > /sys/class/leds/default-led/trigger");
        }
        else if(!strcmp("1", message->payload)){
            system("echo none > /sys/class/leds/default-led/trigger");
            system("echo 1 > /sys/class/leds/default-led/brightness");
        }
        else if(!strcmp("0", message->payload)){
            system("echo none > /sys/class/leds/default-led/trigger");
            system("echo 0 > /sys/class/leds/default-led/brightness");
        }
    }
    else if(!strcmp(topicName, ATTR_SET_SUB_TOPIC)){
        int led_status = led_json_parse((char*)message->payload);
        if(led_status == -1){
            printf("Failed to parse led status from JSON\n");
        }
        else{
            if(led_status == 1){
                system("echo none > /sys/class/leds/default-led/trigger"); 
                system("echo 1 > /sys/class/leds/default-led/brightness");
            }
            else if(led_status == 3){
                system("echo none > /sys/class/leds/default-led/trigger");
                system("echo 0 > /sys/class/leds/default-led/brightness");
            }
            else if(led_status == 2){
                system("echo heartbeat > /sys/class/leds/default-led/trigger");
            }
        }
    }
    else if(!strcmp(topicName, ATTR_REPORT_TOPIC)){
        printf("Attribute report received: %.*s\n", message->payloadlen, (char*)message->payload);
    }
    else if(!strcmp(topicName, ATTR_REPORT_SUB_TPOIC)){
        printf("Attribute report reply received: %.*s\n", message->payloadlen, (char*)message->payload);
    }
    else{
        printf("Unknown topic: %s\n", topicName);
    }
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

static void connlost(void *context, char* cause){
    printf("\nConnection lost: %s\n", cause);
}

int main(void){
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_willOptions will_opts = MQTTClient_willOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    //创建mqtt客户端对象
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_create(&client, BROKER_ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL))){
        printf("Failed to create MQTT client, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto exit;
    }
    //设置回调
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, NULL))){
        printf("Failed to set callbacks return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }
    //连接mqtt服务器
    will_opts.topicName = WILL_TOPIC;
    will_opts.message = "Unexpected disconnection";
    will_opts.retained = 1;
    will_opts.qos = 0;

    conn_opts.will = &will_opts;
    conn_opts.keepAliveInterval = 30;
    conn_opts.cleansession = true;
    conn_opts.username = USERNAME;
    conn_opts.password = PASSWORD;
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_connect(client, &conn_opts))){
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto destroy_exit;
    }
    printf("Connected to broker %s\n", BROKER_ADDRESS);

    //发布上线消息
    pubmsg.payload = "device online";
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = 0;
    pubmsg.retained = 1;
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_publishMessage(client, WILL_TOPIC, &pubmsg, NULL))){
        printf("Failed to publish message, return code %d\n", rc);
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    }
    //订阅主题
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_subscribe(client, LED_TOPIC, 0))){
        printf("Failed to subscribe to topic %s, return code %d\n", LED_TOPIC, rc);
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    }
    // if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_subscribe(client, ATTR_SET_SUB_TOPIC, 0))){
    //     printf("Failed to subscribe to topic %s, return code %d\n", ATTR_SET_SUB_TOPIC, rc);
    //     rc = EXIT_FAILURE;
    //     goto disconnect_exit;
    // }

    // led状态指示灯线程
    pthread_t cpu_status_id;
    if (pthread_create(&cpu_status_id, NULL, cpu_status_thread, NULL) != 0) {
        perror("Failed to create cpu_status_thread");
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    } else {
        printf("pthread_create cpu_status_thread succeed\n");
        pthread_detach(cpu_status_id); // 分离线程
    }

    //主循环
    while(1){
        sleep(1);
    }

unsubscribe_exit:
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_unsubscribe(client, LED_TOPIC))){
        printf("Failed to unsubscribe from topic %s, return code %d\n", LED_TOPIC, rc);
        rc = EXIT_FAILURE;
        goto disconnect_exit;
    }
    printf("Unsubscribed from topic %s\n", LED_TOPIC);

disconnect_exit:
    if(MQTTCLIENT_SUCCESS != (rc = MQTTClient_disconnect(client, 10000))){
        printf("Failed to disconnect, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }

destroy_exit:
    MQTTClient_destroy(&client);

exit:
    return rc;
}