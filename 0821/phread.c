#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

void *tfun(void *arg){
	printf("hello world\n");
	printf("%s\n", (char *)arg);
	printf("pid = %d\ntid = %ld\n", getpid(), pthread_self());
	return NULL;
}

void syserr(const char *str){
	perror(str);
	exit(1);
}

int main(){
	pthread_t tid;
	pid_t pid;
	tid = pthread_self();
	pid = getpid();
	printf("tid = %ld\n", tid);
	printf("pid = %d\n", pid);
	int ret = pthread_create(&tid, NULL, tfun, "hello world");
	if(ret != 0){
		syserr("pthread_create err");
	}
	printf("son tid = %ld\n", tid);
	pthread_join(tid, NULL);
	return 0;
}
