#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void syserr(char *str){
	sprintf(str, " %s", "error");
	perror(str);
	exit(1);
}

int main(){
	int res = 0;
	char r_buf[128] = {0};
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		syserr("socket");
	}

	//绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");
	res = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	if(res == -1){
		syserr("bind");
	}
	//收发消息
	struct sockaddr_in addr_s;
	socklen_t len = sizeof(addr_s);
	while(1){
		memset(r_buf, 0, sizeof(r_buf));
		recvfrom(fd, r_buf, sizeof(r_buf), 0, (struct sockaddr *)&addr_s, &len);
		printf("%s\n", r_buf);
	}
	return 0;
}
