#include <stdio.h>
#include <string.h>

#define length 64

char* cut_out(char* arr, int m, int n);

int main(){
	char arr[length] = {0};	//存放读入的字符串
	int m = 0;		//存放起始位置
	int  n = 0;		//存放结束位置
	char* p = NULL;
	printf("请输入一串字符：\n");
	scanf("%s", arr);
	getchar();
	while(1){	//读入截取区间，并判断是否合法
		printf("请输入起始位置：\n");
		scanf("%d", &m);
		getchar();
		printf("请输入结束位置：\n");
		scanf("%d", &n);
		getchar();
		if(m < n)
			break;
		else
			printf("截取区间非法，请重新输入：\n");
	}
	//获取截取后的字符串并打印
	p = cut_out(arr, m, n);	
	printf("截取后的字符串是：\n%s\n", p);
	return 0;
}

/*
	功能：截取指定区间的字符串，并返回截取的字符串地质
	参数：arr存放读入字符串地址，m，n存放截取区间
	返回值：cut截取后的字符串地址
*/
char* cut_out(char* arr, int m, int n){
	static char cut[length] = {0};
	for(int i = m - 1; i < n; i++){
		*(cut + i - m + 1) = *(arr + i);
	}
	
	return cut;
}













