#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
char str[256] = {0};

void *tfun(void *arg);
int main(){
	//初始化互斥锁
//	pthread_mutex_init(&lock, NULL);
	//创建线程
	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, tfun, NULL);
	pthread_create(&tid2, NULL, tfun, NULL);
	pthread_create(&tid3, NULL, tfun, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	//销毁互斥锁
//	pthread_mutex_destroy(&lock);
	return 0;
}

void *tfun(void *arg){
	pthread_mutex_lock(&lock);
	strcpy(str, "hello");
	printf("%s\t", str);
	sleep(1);
	strcpy(str, "world");
	printf("%s\n", str);
	sleep(1);
	pthread_mutex_unlock(&lock);
	return NULL;
}


