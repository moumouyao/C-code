//输入正整数，将正整数分解质因数。质因数要满足两个条件:1）是这个数的因数;2）是质
//数（素数） 如： 6 = 2 * 3      12 = 2 * 2 * 3
//
#define _CRT_SECURE_NO_WARNINGS  1;
#include <stdio.h>

void achieve(int input) {
	int tmp1 = 0, tmp2 = 0, i = 2;
	if (input < 2) {
		//printf("%d", input);
		return;
	}
	while (1) {
		tmp1 = input / i;
		tmp2 = input % i;
		if (tmp2 != 0)		//分解
			i++;
		else
			break;
	}
	printf("%d  ", i);
	if (tmp1 > 1)
		printf("* ");

	achieve(tmp1);

}


int main() {
	int input = 0;

	while (1) {			//读入一个正整数
		printf("请输入一个正整数：\n");
		scanf("%d", &input);
		if (input > 0)
			break;
		else
			printf("输入非法请重新输入！！！\n");
	}
	printf("%d = ", input);
	achieve(input);

	return 0;
}
