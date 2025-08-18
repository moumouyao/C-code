#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
	char r_buf[128] = {0};
	char w_buf[128] = {0};
	//创建套接字	ipv4 tcp
	int fd1 = socket(AF_INET, SOCK_STREAM, 0);
	if(fd1 == -1){
		perror("socket error");
		return -1;
	}
	printf("fd1 = %d\n", fd1);
	//连接服务器
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");

	int res = connect(fd1, (struct sockaddr *)&addr, sizeof(addr));
	if(res == -1){
		perror("connect error");
		return -1;
	}
	while(1){
		printf("请输入向服务器发送的内容\n");
		scanf("%s", w_buf);
		getchar();
		send(fd1, w_buf, sizeof(w_buf), 0);
		memset(w_buf, 0, sizeof(w_buf));
		recv(fd1, r_buf, sizeof(r_buf), 0);
		printf("从服务器接收到：%s\n", r_buf);
	}
	close(fd1);

	return 0;
}
