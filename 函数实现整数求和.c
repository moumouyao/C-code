#include <stdio.h>

int Sum_Of_Intervals(int m, int n);

int main(){
	int m, n, sum;
	printf("������������䣺\n");
	scanf("%d%d", &m, &n);
	sum = Sum_Of_Intervals(m, n);
	printf("%d��%d֮�������������Ϊ%d\n", m, n, sum);
	return 0;
}


/*
	��飺��m��n֮������������
	�������β�int m, int n, 
	����ֵ��int sum
*/
int Sum_Of_Intervals(int m, int n){
		int sum = 0;
		if( m > n){		//�жϴ�С��ϵ
			int tmp = m;
			m = n;
			n = tmp;
		}
		while( ++m < n){	//���
			sum = sum + m;
		}
		return sum;
	}
	
	
	
	
	
	
	
	