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
	char w_buf[128] = {0};
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		syserr("socket");
	}

	//收发消息
	struct sockaddr_in addr_s;
    addr_s.sin_family = AF_INET;
    addr_s.sin_port = htons(12345);
    addr_s.sin_addr.s_addr = inet_addr("192.168.106.130");
	socklen_t len = sizeof(addr_s);
	while(1){
		memset(w_buf, 0, sizeof(w_buf));
		printf("请输入要发送的内容：\n");
        scanf("%s",w_buf);
        getchar();
		sendto(fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&addr_s, len);
	
	}
	return 0;
}
