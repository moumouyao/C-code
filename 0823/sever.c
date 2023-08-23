#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
	char w_buf[128] = {0};
	char r_buf[128] = {0};
	//创建套接字	ipv4 tcp
	int fd1 = socket(AF_INET, SOCK_STREAM, 0);

	if(fd1 == -1){
		perror("socket error");
		return -1;
	}
	//绑定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("192.168.106.130");

	int res = bind(fd1, (struct sockaddr *)&addr, sizeof(addr));
	if(res == -1){
		perror("bind error");
		return -1;
	}
	//设置最大监听数量
	res = listen(fd1, 3);
	if(res == -1){
		perror("listen error");
		return -1;
	}
	//等待连接，生成套接字
	struct sockaddr_in o_addr;
	socklen_t len = sizeof(o_addr);
	printf("等待客户端连接\n");
	int cfd = accept(fd1, (struct sockaddr *)&o_addr, &len);
	if(cfd == -1){
		perror("accpet error");
		return -1;
	}
	
	printf("客户端已连接\n");
	while(1){
		res = recv(cfd, r_buf, sizeof(r_buf), 0);
		if(res == 0){
			printf("客户端已下线，退出连接\n");
			break;
		}
		printf("从客户端接收到：%s\n", r_buf);
		printf("请输入向客户端发送的信息\n");
		scanf("%s", w_buf);
		getchar();
		send(cfd, w_buf, sizeof(w_buf), 0);

	}

	return 0;
}
