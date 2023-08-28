#include <common.h>

//函数声明
void clear();
void clears();
void syserr(const char *str, int ret);
int CREATID();
void printf_info(DATA data, char *str);

//全局变量
int cfd[MAXLINK] = {0};
int count = 0;

int main(){
	int sockfd;
	int ret, maxfd;
	socklen_t len = 0;
	struct sockaddr_in s_addr, c_addr;
	fd_set readset, bpset;
	DATA r_data;
	//连接数据库
	MYSQL *con = mysql_init(NULL);
	con = mysql_real_connect(con, "localhost", "root", "1", "userdatas", 0, NULL, 0);
	if(con == NULL){
		printf("数据库连接失败\n");
		return -1;
	}



	//建立监听套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	maxfd = sockfd;
	//绑定端口和IP
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(NETPORT);
    s_addr.sin_addr.s_addr = inet_addr(S_ADDR);	
	ret = bind(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr));
	if(ret == 1){
		syserr("bind", ret);
	}
	//设置最大监听数量
	ret = listen(sockfd, MAXLINK);
	if(ret == -1){
		syserr("listen", ret);
	}
	//select集中阻塞
	FD_ZERO(&bpset);	//清理合集
	FD_SET(sockfd, &bpset);	//将套接字添加进合集
	while(1){
		readset = bpset;
		ret = select(maxfd + 1, &readset, NULL, NULL, NULL);	//阻塞等待异动
		if(FD_ISSET(sockfd, &readset)){
			len = sizeof(c_addr);
			cfd[count] = accept(sockfd, (struct sockaddr *)&c_addr, &len);	//sockfd异动
			if(maxfd < cfd[count]){
				maxfd = cfd[count];
			}
			FD_SET(cfd[count], &bpset);	//更新阻塞合集
			count ++;
			if(ret == 1){
				continue;
			}
		}
		for(int i = 0; i < count; i++){
			if(FD_ISSET(cfd[i], &readset)){
				memset(&r_data, 0, sizeof(r_data));
				ret = recv(cfd[i], &r_data, sizeof(r_data), 0);
				if(ret > 0){
					if(r_data.type == 3){
					r_data.id = CREATID();
					if(r_data.id == -1){
						strcpy(r_data.feedback, "账号创建失败");
					}
					// 执行插入数据的SQL语句
					char query[1000];
					sprintf(query, "INSERT INTO user (id, user, passwd) VALUES (%d, '%s', '%s')", r_data.id, r_data.name, r_data.passwd);
					
					  if ( 	mysql_query(con, query) != 0) {
							printf("%s\n", mysql_error(con));
							strcpy(r_data.feedback, "账号创建失败");
							 }
					  else{
						strcpy(r_data.feedback, "账号创建成功");
						}
					  send(cfd[i], &r_data, sizeof(r_data), 0);
					  //打印操作信息
					  printf_info(r_data, "账号创建成功");
				}
					else if(r_data.type == 4){	//登录
						//执行SQL语句(上午给大家讲的指令)，获取表格中的内容。
						char buf[255] = {0};
						int flog = 0;
						sprintf(buf,"select * from user");
						int res = mysql_query(con,buf);
						if(res != 0)
						{
							printf("获取表格内容失败\n");
							 return -1;
						}
						MYSQL_RES *t = mysql_store_result(con);
				//		int row = 0;	//行数
				//		int column = 0;	//列数
				//		column = mysql_num_fields(t);
			//			row = mysql_num_rows(t);
				//		MYSQL_FIELD *b;
						char **a;
						//char buf[64] = {0};
						while(a == mysql_fetch_row(t)){
							memset(buf, 0, sizeof(buf));
							sprintf(buf, "%d", r_data.id);
							if((!strcmp(buf, a[0])) && (!strcmp(r_data.passwd, a[2])) ){
								strcpy(r_data.feedback, "登录成功");
								flog = 1;
								break;
							}
						}
						if(flog == 0){
							strcpy(r_data.feedback, "登录失败");
						}
						send(cfd[i], &r_data, sizeof(r_data), 0);
						printf_info(r_data, "登录成功");
					}
					
					/*printf( "%s\t", ctime(&rawtime));
					if(!strcmp(r_data.feedback, "账号创建成功")){
						printf("%s  用户名：%s  账号：%d\n", r_data.feedback, r_data.name, r_data.id);
					}
					else{
						printf("%s  %s\n", r_data.feedback, r_data.name);
					}*/
				}
				else if(ret == 0){
					FD_CLR(cfd[i], &bpset);
					sprintf(r_data.w_buf, "%s下线\n", r_data.name);
					//群发下线提醒
					for(int j = 0; j < count; j++){
						//屏蔽自己和不在线的用户
						if(i != j){
							send(cfd[j], &r_data, sizeof(r_data), 0);
						}
					}
						for(int k = i; k < count -1; k++){
							cfd[k] = cfd[k + 1];
						}
						count --;
					
				}
			}
		}

	}
    // 关闭MySQL连接
    mysql_close(con);

	return 0;
}
//打印信息
void printf_info(DATA data, char *str){
	time_t rawtime;
	time(&rawtime);
	printf( "%s\t", ctime(&rawtime));
	if(!strcmp(data.feedback, str)){
		printf("%s  用户名：%s  账号：%d\n", data.feedback, data.name, data.id);
	}
	else{
		printf("%s  %s\n", data.feedback, data.name);
	}
}
//创建账号
int CREATID(){
	int init_id = 20230828;
	int fd = 0;
	if(((fd = open("id.txt", O_RDWR | O_CREAT, 0664)) == -1)){
		perror("open");
		return -1;
	}
	if((read(fd, &init_id, sizeof(init_id))) == -1){
		perror("read");
		return -1;
	}
	init_id ++;
	lseek(fd, 0, 0);
	write(fd, &init_id, sizeof(init_id));
	close(fd);
	return init_id;
}

//TCP初始化
void tcp_init(){

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
