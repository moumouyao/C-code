#include <stdio.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
	
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket error");
		return -1;
	}
	//绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");
	if(bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		perror("bind error");
		return -1;
	}
	//接收信息
	char r_buf[128] = {0};
	
	struct sockaddr_in addr_i;
	socklen_t len = sizeof(addr_i);
	while(1){
	
		recvfrom(fd, r_buf, sizeof(r_buf), 0, (struct sockaddr *)&addr_i, &len);
		printf("接受到的消息\n%s\n", r_buf);
	}
	return 0;
}
