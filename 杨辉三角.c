#include <stdio.h>

#define row 10	//����������
#define col 10	//S����������


int main() {
	int num[row][col] = { {1},
						 {1, 1}
	};	//���ԭ����

	//��ֵ
	for (int i = 0; i < row; i++) {
		num[i][0] = 1;
		num[i][i] = 1;
		for (int j = 1; j < i; j++) {
			num[i][j] = num[i - 1][j] + num[i - 1][j - 1];
		}
	}

	//��ӡ
	for (int i = 0; i < row; i++) {
		for (int j = 0; j <= i; j++) {
			printf("%d\t", num[i][j]);
		}
		printf("\n");
	}



	return 0;
}








