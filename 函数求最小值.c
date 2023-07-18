#include <stdio.h>

//求最小值
int Max(int i, int j);

int main(){
	int i, j;	//存放读入数据
	printf("请输入需要比较大小的两个数据：\n");
	scanf("%d%d", &i, &j);
	printf("最小值是%d\n", Max(i, j));
	 
	return 0;
}


int Max(int i, int j){
	return (i > j) ? j : i;
}