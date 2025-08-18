#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//静态创建互斥锁
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//定义全局条件变量
pthread_cond_t cond;

void *tfun1(void *p);
void *tfun2(void *p);


int main(){
	//初始化条件变量
	pthread_cond_init(&cond, NULL);
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, tfun1, NULL);
	pthread_create(&tid2, NULL, tfun2, NULL);
	//等待
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	//销毁
	pthread_mutex_destroy(&lock);

	pthread_cond_destroy(&cond);
	return 0;
}

void *tfun1(void *P){
	printf("小红在等车\n");
	//阻塞
	pthread_cond_wait(&cond, &lock);
	printf("小红上车\n");
	return NULL;
}

void *tfun2(void *p){
	sleep(10);
	printf("车到了\n");
	pthread_cond_signal(&cond);
	return NULL;
}
