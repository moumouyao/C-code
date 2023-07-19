#include <stdio.h>

//声明一个结构体类型
struct Date{
	int year;
	int month;
	int day;
};

int calculate(struct Date date);

int main(){
	//date	用来存放日期
	struct Date date;	
	int  sum;		//存放总天数以及返回值
	//读入年月日
	printf("请输入年份\n");
	scanf("%d", &date.year);
	getchar();
	printf("请输入月份\n");
	scanf("%d", &date.month);
	getchar();
	printf("请输入日份：\n");
	scanf("%d", &date.day);
	getchar();
	sum = calculate(date);
	//错误判断
	if(sum == -1)
		printf("输入的年份错误\n");
	else if(sum == -2)
		printf("输入的月份错误错误\n");
	else if(sum == -3)
		printf("输入的日份错误\n");
	else
		printf("总天数为：%d\n", sum);	//打印总天数
	
	return 0;
}

/*
	功能：计算某年开始到某个日期一共多少天
	参数：struct Date date	年月日
	返回值：-1	输入年份错误
		   -2	输入月份错误
		   -3	输入日份错误
		   其他值	总天数
*/
int calculate(struct Date date){
	int flag1 = 0;	//输入月份标志位
	int flag2 = 0;	//闰年，平年标志位
	int sum = 0;	//总天数
	
	if(date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)
		flag1 = 1;		//每月31天
	else if(date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
		flag1 =2;		//每月30天
	else if(date.month == 2)
		flag1 = 5;		//二月
		
		if(date.year % 400 == 0 || date.year % 4 == 0 && date.year % 100 != 0)
			flag2 = 3;	//闰年
		else
			flag2 = 4;	//平年
	
		
	//错误判断	
	if(date.year <= 0)
		return -1;	//年错误
	else if(flag1 == 0)
		return -2;	//月错误
	else if((flag1 == 1 && (date.day < 0 || date.day > 31)) || (flag1 == 2 && (date.day < 0 || date.day > 30)) ||((flag1 == 5 && flag2 == 3) && (date.day < 0 || date.day > 29)) || ((flag1 == 5 && flag2 == 4) &&(date.day < 0 || date.day > 28)))
		return -3;	//日错误
	
	//计算天数
	for(int i = 1; i < date.month; i++){	//除了2月和输入月份的总天数
		if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			sum = sum + 31;
		else if(i == 4 || i == 6 || i == 9 || i == 11)
			sum = sum + 30;
	}
	if(date.month > 2){	//输入月份是否大于2月
		if(flag2 == 3)
			return sum + 29 + date.day;	//闰年
		else
			return sum + 28 + date.day;	//平年
	}
	else
		return sum + date.day;			//输入月份小于2月
	
}


