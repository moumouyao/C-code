#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

void sfun(int sig);

void *tfun(void *arg);
int main(){
	//创建线程
	pthread_t tid;
	pthread_create(&tid, NULL, tfun, NULL);
	sleep(10);
	pthread_kill(tid, 2);
	pthread_join(tid,NULL);
	return 0;
}

void *tfun(void *arg){
	signal(2, sfun);
	while(1){
		printf("子线程\n");
	sleep(1);	
	}
	return NULL;
}

void sfun(int sig){
	printf("捕获到的信号 ：%d\n", sig);
	
}
