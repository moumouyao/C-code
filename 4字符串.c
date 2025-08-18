#include <stdio.h>
#include <string.h>

#define length 64

int my_strlen(const char *arr);

int main(){
	char arr[length] = {0};
	int n = 0;
	printf("请输入一串字符：\n");
	scanf("%s", arr);
	getchar();
	//求长度并打印
	n = my_strlen(arr);
	printf("字符串的长度为：%d\n", n);
	return 0;
}

/*
	功能：求字符串长度
	参数：const char* arr		字符串首地址
	返回值：n 字符串长度		
	
*/
int my_strlen(const char *arr){
	int n = 0;
	while(*arr++){
		n++;
	}
	return n;
}
