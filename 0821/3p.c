#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void syserr(const char *str){
	perror(str);
	exit(1);

}

void *tfun(void *arg){
	printf("进程序列：%d\n", (int)arg);
	printf("pid = %d\ntif = %ld\n", getpid(), pthread_self());
	return NULL;
}

int main(){
	pthread_t tid;
	for(int i = 0; i < 5; i++){
		pthread_create(&tid, NULL, tfun, (void *)i);

		//pthread_join(tid, NULL);
	}
//		while(!pthread_join(tid, NULL));
		sleep(1);
	printf("主线程\npid = %d\ntid = %ld\n", getpid(), pthread_self());
	return 0;
}
