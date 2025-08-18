#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void * fun(){
	printf("hello\n");
	pthread_exit(NULL);
	printf("world\n");
	return NULL;
}

void syserr(const char *str){
	perror(str);
	exit(1);

}

void *tfun(void *arg){
	int i = (int)arg;
	sleep(i);
	printf("进程序列：%d\n", i);
	if(i == 3){
		//exit(0);
		fun();
		printf("hello world\n");
	}
	printf("pid = %d\ntif = %ld\n", getpid(), pthread_self());
	return NULL;
}

int main(){
	pthread_t tid;
	int i = 0;
	for(i = 0; i < 5; i++){
		pthread_create(&tid, NULL, tfun, (void *)i);

		//pthread_join(tid, NULL);
	}
//		while(!pthread_join(tid, NULL));
//		sleep(i);
	//	pthread_exit(NULL);
	printf("主线程\npid = %d\ntid = %ld\n", getpid(), pthread_self());
//	return 0;
	pthread_exit(NULL);
}
