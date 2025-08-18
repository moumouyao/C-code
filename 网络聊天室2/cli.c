#include <common.h>

//函数声明
void clear();
void clears();
void syserr(const char *str, int ret);
void create_account(void);
enum log_in menu1();
void contin();
int connect_ser();
void disconnect(int sockfd);
void login();
enum after_log_in menu2();
void chat();
void *W_FUN(void *arg);
void group_chat();
int main(){
	int num = 0;
	while(1){
		num = menu1();
		switch(num){
			case LOG_IN: login();
						
				break;
			case REGISTER:	create_account();
							
				break;
			case QUIT:	printf("网络聊天室已退出\n"); return 0;
				break;
		}
	}

	return 0;
}

void chat(){
	int num = 0;
	while(1){
		num = menu2();
		switch(num){
			case GROUP_CHAT: group_chat();	
				break;
			case PRIVATE_CHAT:
				break;
			case REMOVE:
				break;
			case LOG_OUT:
				break;
			case DELETE:
				break;
		}
	}

}
//子线程调用函数，用于发送消息
void *W_FUN(void *arg){
	DATA data;
	int sockfd = (int)arg;
	data.type = 1;
	printf("请写入想要发送的内容\n");
	scanf("%s", data.w_buf);
	clear();
	send(sockfd, &data, sizeof(data), 0);
	memset(&data, 0, sizeof(data));
	return NULL;
}
//群聊
void group_chat(){
	DATA data;
	time_t rawtime;
	int sockfd = 0;
	pthread_t pid;
	data.type = 1;	//标志位设为群聊
	sockfd = connect_ser();
	if(sockfd == -1){
		printf("连接服务器失败\n");
		return ;
	}
	pthread_create(&pid, NULL, W_FUN, (void *)sockfd);
	while(1){
		printf("11\n");
		recv(sockfd, &data, sizeof(data), 0);
		time(&rawtime);
		printf("%s", ctime(&rawtime));
		printf("%s\n", data.r_buf);
		printf("124\n");
		memset(&data, 0, sizeof(data));
	}
	disconnect(sockfd);
}

//登录函数
void login(){
	DATA data;
	int sockfd = 0;
	time_t rawtime;

	while(1){
		printf("请输入账号\n");
		scanf("%d", &data.id);
		clear();
		printf("请输入密码\n");
		scanf("%s", data.passwd);
		clear();
		data.type = 4;	//设置标志位为登录
		//发送账号，检测是否存在
		//连接客户端
		sockfd = connect_ser();
		if(sockfd == -1){
			printf("连接服务器失败\n");
			return;
		}
		send(sockfd, &data, sizeof(data), 0);
		recv(sockfd, &data, sizeof(data), 0);

		time(&rawtime);
		printf("%s", ctime(&rawtime));
		if(!strcmp(data.feedback, "登录成功")){

			printf("%s\n", data.feedback);
			printf("用户名：%s  账号%d\n", data.name, data.id);
			contin();
			chat();
			break;

		}
		else{
			printf("%s\n", data.feedback);
			contin();
			break;
		}
		//断开连接
		disconnect(sockfd);
	}	
}

//注册函数
void create_account(void){
	DATA w_data, r_data;
	char pws1[32] = {0}, pws2[32] = {0};
	int   sockfd = 0;
	//创建账户
	printf("请输入用户名\n");
	scanf("%s", w_data.name);
	clear();
	clears();
	printf("用户名设置成功\n");
	while(1){
		printf("请输入密码\n");
		scanf("%s", pws1);
		clear();
		clears();
		printf("请再次输入密码\n");
		scanf("%s", pws2);
		clear();
		
		if(!strcmp(pws1, pws2)){
			clears();
			strcpy(w_data.passwd, pws1);
			printf("密码创建成功\n");
			break;
			}
		else{
			clears();
			printf("密码输入不一致，请重新输入\n");
		}
	}
	w_data.type = 3;
	//发送给服务器
	sockfd = connect_ser();
	if(sockfd == -1){
	printf("连接服务器失败\n");
	return;
	}
	send(sockfd, &w_data, sizeof(w_data), 0);
	recv(sockfd, &r_data, sizeof(r_data), 0);
	//断开连接
	disconnect(sockfd);
	if(!strcmp(r_data.feedback, "账号创建成功")){
		printf("%s\n", r_data.feedback);
		printf("用户名：%s  账号%d\n", r_data.name, r_data.id);
		contin();
	}
	else{
		printf("%s\n", r_data.feedback);
		contin();
	}
}

//断开与服务器连接
void disconnect(int sockfd){
	 shutdown(sockfd, SHUT_RDWR); // 断开连接
	 close(sockfd); // 关闭套接字,释放资源
}

//连接服务器
int connect_ser(){
	int sockfd = 0, ret = 0;
	struct sockaddr_in s_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		
		//syserr("socker", sockfd);
		perror("socket");
		return -1;
	}
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(NETPORT);
	s_addr.sin_addr.s_addr = inet_addr(S_ADDR);
	ret = connect(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret == -1){
		perror("connect");
		//syserr("connect", ret);
		return -1;
	}
	return sockfd;

}

//菜单	登录界面菜单
enum log_in menu1(){
	enum log_in num;

	while(1){
		printf("%d.登录\n", LOG_IN);
		printf("%d.注册\n", REGISTER);
		printf("%d.退出\n", QUIT);
		printf("请选择功能\n");
		scanf("%d",(int *)&num);
		clear();
		if(num > QUIT || num < LOG_IN){
			clears();
			printf("非法输入，请重新输入\n");
		}
		else{
			clears();
			return num;
		}
	}

}
//菜单	登录之后菜单
enum after_log_in menu2(){
	enum after_log_in num;

	while(1){
		printf("%d.群聊\n", GROUP_CHAT);
		printf("%d.私聊\n", PRIVATE_CHAT);
		printf("%d.移除群聊\n", REMOVE);
		printf("%d.退出登录\n", LOG_OUT);
		printf("%d.注销登录\n", DELETE);
		printf("请选择功能\n");
		scanf("%d",(int *)&num);
		clear();
		if(num > DELETE || num < GROUP_CHAT){
			clears();
			printf("非法输入，请重新输入\n");
		}
		else{
			clears();
			return num;
		}
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

//错误函数
void syserr(const char *str, int ret){
	printf("%s error: %s\n", str, strerror(ret));
	exit(1);
}

//卡点
void contin(){
	char ch = 0;
	printf("按任意键继续\n");
	while(1){
		if(scanf("%c", &ch)){
			clear();
			clears();
			break;
		}
		}
}
