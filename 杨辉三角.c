#include <stdio.h>

#define row 10	//定义数组行
#define col 10	//S定义数组列


int main() {
	int num[row][col] = { {1},
						 {1, 1}
	};	//存放原数组

	//赋值
	for (int i = 0; i < row; i++) {
		num[i][0] = 1;
		num[i][i] = 1;
		for (int j = 1; j < i; j++) {
			num[i][j] = num[i - 1][j] + num[i - 1][j - 1];
		}
	}

	//打印
	for (int i = 0; i < row; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d\t", num[i][j]);
		}
		printf("\n");
	}



	return 0;
}








