#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
	
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket error");
		return -1;
	}
	//发送信息
	char w_buf[128] = {0};
	
	struct sockaddr_in addr_o;
	addr_o.sin_family = AF_INET;
	addr_o.sin_port = htons(12345);
	addr_o.sin_addr.s_addr = inet_addr("192.168.106.130");
	socklen_t len = sizeof(addr_o);
	while(1){
	
		printf("请输入要发送消息\n");
		scanf("%s", w_buf);
		sendto(fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&addr_o, len);
	}
	return 0;
}
