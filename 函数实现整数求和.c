#include <stdio.h>

int Sum_Of_Intervals(int m, int n);

int main(){
	int m, n, sum;
	printf("请输入计算区间：\n");
	scanf("%d%d", &m, &n);
	sum = Sum_Of_Intervals(m, n);
	printf("%d和%d之间的所有整数和为%d\n", m, n, sum);
	return 0;
}


/*
	简介：求m到n之间所有整数和
	参数：形参int m, int n, 
	返回值：int sum
*/
int Sum_Of_Intervals(int m, int n){
		int sum = 0;
		if( m > n){		//判断大小关系
			int tmp = m;
			m = n;
			n = tmp;
		}
		while( ++m < n){	//求和
			sum = sum + m;
		}
		return sum;
	}
	
	
	
	
	
	
	
	