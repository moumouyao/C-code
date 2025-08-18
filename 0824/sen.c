#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
	
	int num = 1;
	//创建套接字
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket error");
		return -1;
	}
	//广播
	int val = 1;
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(int));
	//发送信息
	char w_buf[128] = {0};
	
	struct sockaddr_in addr_o;
	addr_o.sin_family = AF_INET;
	addr_o.sin_port = htons(12345);
	addr_o.sin_addr.s_addr = inet_addr("192.168.106.255");
	socklen_t len = sizeof(addr_o);
	while(1){
		memset(w_buf, 0, sizeof(w_buf));
		sprintf(w_buf, "num = %d", num);
		printf("发送的信息: %s\n", w_buf);
		sendto(fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&addr_o, len);
		sleep(1);
		num ++;
	}
	return 0;
}
