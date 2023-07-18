#include <stdio.h>

#define length 5 //定义数组长度

float Average_Value(float* input, int len);

int main(){
		float input[length] = {0};	//存放读入的数据
		float a = 0;		//存放平均值
		printf("请输入%d组数据：\n", length);
		for(int i = 0; i < length; i ++){	//读入数据
			printf("请输入第%d个数据：\n", i + 1);
			scanf("%f", &input[i]);
		}
		a = Average_Value(input, length);	//求平均值
		printf("这%d组数据的平均值是%.2f\n", length, a);
	return 0;
}


/*
	简介：浮点数求和
	参数：float* input 数组首地址	int length 数组长度
	返回值：sum / length 平均值
*/
float Average_Value(float* input, int len){
			float sum = 0;
			for(int i = 0; i < length; i++){
				sum = sum + *(input + i);
			}
			return sum / length;
}
