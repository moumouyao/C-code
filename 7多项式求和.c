#include <stdio.h>

void Multinomial(int n);

int main(){
	int n = 0;
	printf("请输入n的值:\n");
	scanf("%d", &n);
	Multinomial(n);
	return 0;
}


/*
	简介：1 / n多项式求和，并打印
	参数: int i	多项式个数
	返回值：无
*/
void Multinomial(int n){
	float sum = 0;
	for(int i = 1; i <= n; i++){
		printf("1 / %d ", i);
		if(i != n)
			printf("+ ");
		sum = sum + 1.0 / i; 
	}
	printf(" = %.3f\n", sum);
	}

