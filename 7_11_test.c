#include <stdio.h>

int main() {
	//标题
	printf("**********************************************\n");
	printf("*******最大值*****最小值******平均值**********\n");
	printf("**********************************************\n");
	int arr[32] = { 0 };		//存数
	int num = 0;			//数字个数
	int tmp = 0;			//临时存放数据
	int sum = 0;			//求和
	float everage = 0;		//平均值
	//读取数字个数，并判断是否合法
	while (1) {
		printf("请输入需要求值的数字个数(3 ~ 32)：\n");
		scanf("%d", &num);
		if (num > 2 && num < 33)
			break;
		else
			printf("输入非法！！！\n");

	}
	//读取数字
	printf("请输入%d组数字:\n", num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &arr[i]);
		sum = arr[i] + sum;		//求和
	}
	everage = (float)sum / num;	//求平均值
	//求最大值
	for (int i = 0; i < num - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
		}
	}


	//求最小值
	for (int i = num - 2; i >= 0; i--) {
		if (arr[i] < arr[i - 1]) {
			tmp = arr[i];
			arr[i] = arr[i - 1];
			arr[i - 1] = tmp;
		}
	}
	printf("这组数据的最大值为：%d，最小值为：%d，平均值为%f\n", arr[num - 1], arr[0], everage);
	return 0;
}