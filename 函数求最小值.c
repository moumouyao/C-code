#include <stdio.h>

//����Сֵ
int Max(int i, int j);

int main(){
	int i, j;	//��Ŷ�������
	printf("��������Ҫ�Ƚϴ�С���������ݣ�\n");
	scanf("%d%d", &i, &j);
	printf("��Сֵ��%d\n", Max(i, j));
	 
	return 0;
}


int Max(int i, int j){
	return (i > j) ? j : i;
}