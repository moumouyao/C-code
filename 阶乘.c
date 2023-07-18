#include <stdio.h>

int factorial(int num);

int main() {
	int num = 0;
	printf("请输入需要求阶乘的数字：\n");
	scanf("%d", &num);
	printf("%d的阶乘为：%d\n", num, factorial(num));
	return 0;
}



int factorial(int num) {
	int tmp = 1;
	
	if (num > 1) {
		 tmp = factorial(num - 1) * num;

	}
	return tmp;
}










