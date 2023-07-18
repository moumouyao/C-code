#include <stdio.h>

#define length 20	//定义字符数组长度

void Replace(char* arr, char f, char l);

int main(){
	char arr[length] = {0};	//存放输入的字符串
	char f = 0;		//存放替代前的字符
	char l = 0;		//存放替代后的字符
	//读入数据
	printf("请输入一串字符：\n");
	scanf("%s", arr);
	getchar();	//清除回车
	printf("请输入想要被替换掉的字符：\n");
	scanf("%c", &f);
	getchar();	//清除回车
	printf("请输入替换之后的字符：\n");
	scanf("%c", &l);
	//打印字符串
	printf("替换之前的字符串:\n%s\n", arr);
	Replace(arr, f, l);		//替换函数
	printf("替换之后的字符串:\n%s\n", arr);
	return 0;
}



/*
	简介：字符串中某个字符的替换
	参数：char* arr 指向字符串的指针， char f 替换前的字符， char l 替换后的字符
	返回值：无
*/
void Replace(char* arr, char f, char l){
	while(*arr){
		if(*arr == f)
			*arr = l;
	arr++;
	}
}





