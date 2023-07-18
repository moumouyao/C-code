#include <stdio.h>

int highest_common_divissor(int m, int n);
int lowest_common_multiple(int m, int n);

int main(){
	int m, n;	//存放读入数据
	int result;
	//读入数据
	while(1){
	printf("请输入两组数字：\n");
	scanf("%d%d", &m, &n);	
	if(m == 0 || n == 0)
		printf("非法输入，请勿输入0\n");
	else
		break;
	}

	//求最大公因数并打印
	result = highest_common_divissor( m, n);
	printf("最大公因数：%d\n", result);
	//求最小共倍数并打印
	result = lowest_common_multiple( m, n);
	printf("最小共倍数：%d\n", result);
	
	return 0;
}


/*
	功能：递归求最大公因数
	参数：int m, int n
	返回值：最大公因数
*/
int highest_common_divissor(int m, int n){
	int flag = 0;
	if(m < 0){
		m = -m;
		flag = 1;
	}
	if(n < 0){
		n = -n;
		flag = 1;
	}
	if(m > n){
		int tmp = m;
		m = n;
		n = tmp;
	}
	if (n % m != 0) {
		int tmp = n;
		n = m;
		m = tmp % m;
		m = highest_common_divissor(m, n);
	}
	if(flag == 1)
		return -m;
	else
	return m;
}


/*
	功能：求最小公倍数
	参数：int m, int n
	返回值：最小公倍数	
*/
int lowest_common_multiple(int m, int n){
	
	static int flag2 = 0;
	if(m < 0){
		m = -m;
		flag2 = 1;
	}
	if(n < 0){
		n = -n;
		flag2 = 1;
	}	
	int tmp = highest_common_divissor(m, n);
	if(flag2 == 1)
		return - m * n /tmp;
	else
	return m * n /tmp;

	
}









