#include <stdio.h>
#include <string.h>

#define length 128	//定义字符串长度

char* my_strcat(char* arr1, const char* arr2);

int main(){
	char arr1[2 * length] = {0};
	char arr2[length] = {0};
	printf("请输入一串字符：\n");
	scanf("%s", arr1);
	getchar();
	printf("请输入第二串字符：\n");
	scanf("%s", arr2);
	getchar();
	printf("拼接之后的字符串为：\n%s\n", my_strcat(arr1, arr2));
	return 0;
}

/*
	功能：字符串拼接
	参数：char* arr1 拼接字符串首地址	const char* arr2 被拼接字符串首地址
	返回值：char* tmp 拼接字符串首地址
*/
char* my_strcat(char* arr1, const char* arr2){
	char* tmp = arr1;
	while(*arr1){
		arr1++;
	}
	while(*arr1++ = *arr2++);
	*(arr1) = 0;
	return tmp;
}

