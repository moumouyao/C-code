#include <stdio.h>

#define row 2	//定义数组行
#define col 3	//定义数组列

int main(){
	int x = 0, y = 0;//存放最大值坐标
	int max = 0; 	//存放最大值
	int num[row][col] = {0};
	int flag = 0;	//标志位
	//读入数据
	printf("请输入%d组数字：\n", row * col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%d", &num[i][j]);
		}
	}
	//寻找最大值
	max = num[0][0];
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(num[i][j] >= max){
				if(num[i][j] == max)
					flag = 1;
				else
					flag = 0;
				max = num[i][j];
				x = i;
				y = j;
				
			}
		}
	}
	//将数据放在坐标中打印出来
	printf("将这组数字放在一个 %d * %d 的坐标中：\n", row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
	//判断最大值是否唯一
	if(flag == 0){		//一个最大值
		printf("这个组数据中最大值是：%d\n", max);
		printf("它的坐标是：( %d , %d )\n", x + 1, y + 1);
	}
	else{				//多个最大值
		printf("这组数据有多个最大值\n");
		printf("这组数据中最大值是：%d\n", max);
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(num[i][j] == max){
				printf("它的坐标是：( %d , %d )\n", i + 1, j + 1);
				}
		}
	}		
	}
	return 0;
}








