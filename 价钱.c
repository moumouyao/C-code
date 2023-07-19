#include <stdio.h>

//声明一个结构体类型
struct fruit{
	float app;
	float ba;
	float gra;
};

float calculate(struct fruit num, struct fruit price);

int main(){
	//num 用来存放斤数		price用来存放单价
	struct fruit num, price = {5, 6.8, 5.2};	
	float sum;		//存放总价以及返回值
	//读入各种水果斤数
	printf("请输入苹果的斤数\n");
	scanf("%f", &num.app);
	getchar();
	printf("请输入香蕉的斤数\n");
	scanf("%f", &num.ba);
	getchar();
	printf("请分别输入葡萄的斤数\n");
	scanf("%f", &num.gra);
	getchar();
	sum = calculate(num, price);
	//错误判断
	if(sum == -1)
		printf("苹果斤数错误\n");
	else if(sum == -2)
		printf("香蕉斤数错误\n");
	else if(sum == -3)
		printf("香蕉斤数错误\n");
	else
		printf("总价钱为：%.2f\n", sum);	//打印总价
	
	return 0;
}

/*
	功能：计算水果总价
	参数：num 接收斤数		price 接收单价
	返回值：-1	苹果斤数错误
		   -2	香蕉金属错误
		   -3	葡萄斤数错误
		   其他值	总价
*/
float calculate(struct fruit num, struct fruit price){
	if(num.app < 0)
		return -1;
	else if(num.ba < 0)
		return -2;
	else if(num.gra < 0)
		return -3;
	return price.app * num.app + price.ba * num.ba + price.gra * num.gra;
}

