#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <net/if.h>

    struct ip_mreqn{
        struct in_addr imr_multiaddr;  //组播地址
        struct in_addr imr_address;     //本地地址    INADDR_ANY
        int imr_ifindex;    //物理地址    物理硬件id函数  if_nametoindex("ens33")                
    };

int main(){
	
	char w_buf[128] = {0};
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket error");
		return -1;
	}
	//创建套接字组播
	struct ip_mreqn val;
	val.imr_multiaddr.s_addr = inet_addr("225.0.0.1");
	val.imr_address.s_addr = INADDR_ANY;
	val.imr_ifindex = if_nametoindex("ens33");
	setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &val, sizeof(val));
	struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr("225.0.0.1");
	socklen_t len = sizeof(addr);	
	while(1){
	
		printf("请输入要发送消息\n");
		scanf("%s", w_buf);
		sendto(fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&addr, len);
	}
	return 0;
}
