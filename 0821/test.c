#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

void syserr(const char *str){
	perror(str);
	exit(1);
}

int main(){
	pid_t pid;
	pid = fork();
	int fd = 0;
	if(pid > 0){
		exit(0);	//父进程终止
	}

	pid = setsid();	//创建新会话
	if(pid == -1){
		syserr("setsid err");
	}
	if(chdir("/home/yyy/linux/0821") == -1){	//改变工作目录位置
		syserr("chdir err");
	}
	umask(0022);	//改变文件访问权限掩码
	close(STDIN_FILENO);	//关闭文件描述符 0
	fd = open("/dev/null", O_RDWR);	//
	if(fd == -1){
		syserr("open err");
		}
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);
	while(1);

	return 0;
}

