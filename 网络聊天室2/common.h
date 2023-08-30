#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//网络端口
#define NETPORT 12345
//最大监听数量
#define MAXLINK 150
//ip地址
#define C_ADDR "192.168.106.130" // 客户端IP地址
#define S_ADDR "192.168.106.130" // 服务器IP地址

//TCP通信所用的结构体
typedef struct{
	char name[32];		//用户名
	char passwd[32];	//用户密码
	int	id;				//用户id
	int  type;			//消息类型， 1 群聊  2 私聊  3 创建账号  4 登录  5 【报错
	char feedback[64];	//反馈信息，服务器处理结果
	int online;			//在线 1 下线 0
	char r_buf[1024];	//读到的信息
	char w_buf[1024];	//写入的信息
	int s_id;			//私聊对象id
	int adm;			//管理员标志位
}DATA;
//

//登录界面枚举菜单
enum log_in {LOG_IN = 1, REGISTER, QUIT};
//登录后菜单枚举
enum after_log_in {GROUP_CHAT = 1, PRIVATE_CHAT, REMOVE, LOG_OUT, DELETE};
