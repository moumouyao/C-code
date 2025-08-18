#include <stdio.h>

#define row 3	//定义数组行
#define col 3	//S定义数组列


int main(){
	int num1[row][col] = {0};	//存放原数组
	int num2[col][row] = {0};	//存放转置后的数组
	
	//读入数据
	printf("请输入%d组数字：\n", row * col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%d", &num1[i][j]);
		}
	}
	//对矩阵进行转置
	for(int i = 0; i < row; i++){	
		for(int j = 0; j < col; j++){	
			num2[j][i] = num1[i][j];
		}
	}

	//打印原矩阵
	printf("将这组数字放在一个 %d * %d 的矩阵中：\n", row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num1[i][j]);
		}
		printf("\n");
	}
	//打印转置后的矩阵
	printf("转置后的矩阵：\n");
	for(int i = 0; i < col; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num2[i][j]);
		}
		printf("\n");
	}
		
		
		
	
	return 0;
}








