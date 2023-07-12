
#include <stdio.h>

#define row 3	//定义数组行
#define col 4	//定义数组列


int main() {
	int num[row][col] = { 0 };	//存放原数组
	int all[col] = { 0 };			//存放总成绩
	float eve1[col] = { 0 };		//存放各科平均成绩
	float eve2[row] = { 0 };		//存放每个同学的平均成绩
	float tmp = 0;				//存放临时变量
	int c = 0;					//


	//读入成绩
	for (int i = 0; i < row; i++) {
		printf("请输入第%d位同学的%d科成绩\n", (i + 1), col);
		for (int j = 0; j < col; j++) {
			printf("请输入第%d科成绩:\n", (j + 1));
			scanf("%d", &num[i][j]);
		}
	}
	//
	for (int i = 0; i < row; i++) {
		tmp = 0;
		for (int j = 0; j < col; j++) {
			tmp = num[i][j] + tmp;		//求每个同学总成绩
		}
		all[i] = tmp;
		eve2[i] = all[i] / (float)col;		//求每个同学的总平均成绩
	}
	//求各科平均成绩
	for (int j = 0; j < col; j++) {
		tmp = 0;
		for (int i = 0; i < row; i++) {
			tmp = num[i][j] + tmp;		//单科总成绩
		}
		eve1[j] = tmp / row;		//单科平均成绩
	}
	//求各科平均成绩
	for (int i = 0; i < row; i++) {
		printf("第%d位同学的各科成绩：\t", i + 1);
		for (int j = 0; j < col; j++) {
			printf("%d\t", num[i][j]);
		}
		printf("\n");
	}
	//打印最高成绩
	tmp = all[0];
	for (int i = 0; i < row - 1; i++) {
		if (all[i] > tmp) {
			tmp = all[i];
			c = i;
		}


	}
	printf("\n");
	//打印最高成绩
	printf("第%d位的总成绩最高是%.1f\n", c + 1, tmp);
	printf("\n");

	//打印各科平均成绩
	for (int i = 0; i < col; i++) {
		printf("第%d科的平均成绩为%.1f\n", i + 1, eve1[i]);
	}
	printf("\n");
	//打印每个同学平均成绩
	for (int i = 0; i < row; i++) {
		printf("第%d位同学的平均成绩为%.1f\n", i + 1, eve2[i]);
	}





	return 0;