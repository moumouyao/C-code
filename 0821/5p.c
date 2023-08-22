#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

struct test{
	int val;
	char str[256];
};



void syserr(const char *str){
	perror(str);
	exit(1);

}

void *tfun(void *arg){
	printf("子线程 pid = %d\ntif = %ld\n", getpid(), pthread_self());
	struct test *sp;
	sp = (struct test *)malloc(sizeof(struct test));
	memset(sp, 0, sizeof(struct test));
	sp->val = 128;
	strcpy(sp->str, "子线程 hello world");
	return (void *)sp;
}

int main(){
	pthread_t tid;
	struct test *ret;
		printf("主线程\npid = %d\ntid = %ld\n", getpid(), pthread_self());
	if(pthread_create(&tid, NULL, tfun, NULL) != 0){
		syserr("pthread_create");
	}
	if(pthread_join(tid, (void **)&ret) != 0){
		syserr("pthread_join");
	}
	printf("子线程所赋的值：\nval = %d\nstr = %s\n", ret->val, ret->str);
//	return 0;
	pthread_exit(NULL);
}
