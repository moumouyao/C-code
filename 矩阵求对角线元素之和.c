#include <stdio.h>

#define row 3	//定义数组行


int main(){
	int sum = 0; 	//存放对角线元素和
	int num[row][row] = {0};
	//读入数据
	printf("请输入%d组数字：\n", row * row);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			scanf("%d", &num[i][j]);
		}
	}
	//求对角线元素和
	for(int i = 0; i < row; i++){	//正对角线求和
		sum = num[i][i] + sum;
	}
	for(int i = 0; i < row; i++){	//负对角线求和
	sum = num[i][row - i -1] + sum;
	}
	if(row / 2 == 1)	//矩阵行数为偶数时，减去一个加了两次的中心元素
		sum = sum - num[row / 2 + 1][row / 2 + 1]
	//将数据放在坐标中打印出来
	printf("将这组数字放在一个 %d * %d 的矩阵中：\n", row, row);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
		//打印对角线元素和	
		printf("这个矩阵的对角线元素和是：%d\n", sum);
		
	
	return 0;
}








