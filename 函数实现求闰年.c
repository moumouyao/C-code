#include <stdio.h>

void Judge_leap_year(int i);

int main(){
	int y = 0;		//存放年份
	printf("请输入一个年份：\n");
	while(1){
		scanf("%d", &y);
		if(y >= 0)
			break;
		printf("输入非法，请重新输入：\n");
	}
	Judge_leap_year(y);
			
	return 0;
}


/*
	简介： 判断是否为闰年，并打印
	参数： int y 传入年份
	返回值：无
*/
void Judge_leap_year(int i){
	if(i % 400 == 0 || i % 4 == 0 && i % 100 != 0)
		printf("%d是闰年\n", i);
	else
		printf("%d不是闰年\n", i);
}