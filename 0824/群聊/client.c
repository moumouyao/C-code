#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void syserr(char *str){
	sprintf(str, " %s", "error");
	perror(str);
	exit(1);
}

void *tsend(void *arg);
void *trecv(void *arg);
void clear();
void clears();

int main(){
	pthread_t tid1, tid2;
	int ret = 0;
	ret = pthread_create(&tid1, NULL, tsend, NULL);
	if(ret != 0){
			syserr("pthread_creat");
		}
	
	ret = pthread_create(&tid2, NULL, trecv, NULL);
	if(ret != 0){
			syserr("pthread_creat");
		}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);	
	
	return 0;
}

void *tsend(void *arg){
	int fd = 0;
	int ret = 0;
	char w_buf[128] = {0};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		syserr("socket");
	}
	//连接服务器
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");
	ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1){
		syserr("connect");
	}
	while(1){
		printf("请输入\n");
		scanf("%s", w_buf);
		clear();
		send(fd, w_buf, sizeof(w_buf), 0);
		memset(w_buf, 0, sizeof(w_buf));

	}
	close(fd);
	return NULL;
}

void *trecv(void *arg){
	char r_buf[128] = {0};
	int ret = 0;
	//创建套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1){
		syserr("socket");
	}
	//绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");
	ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1){
		syserr("bind");
	}
	while(1){
		recv(fd, r_buf, sizeof(r_buf), 0);
		printf("接收到的信息\n");
		printf("%s", r_buf);
		memset(r_buf, 0, sizeof(r_buf));
	}
}


//清理缓存区
void clear(){
	while(getchar() != '\n');
}

//清屏
void clears() {
    printf("\033[2J\033[1;1H");
}

