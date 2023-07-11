
#include "Game.h"


//棋盘初始化	0代表空	1代表雷	*显示画面
//mine[][]全置0 、show[][]全置*
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = set;
		}
	}
}

//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col) {
	
	for (int i = 0; i < 10; i++) {		//打印行号
		printf("%d ", i);
	}
	printf("\n");

	for (int i = 1; i <= row; i++) {
		printf("%d ", i);		//打印列号
		for (int j = 1; j <= col; j++) {		//打印棋盘内容
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}


//布雷
void SetMine(char board[ROWS][COLS], int row, int col){

	int count = EasyCount;
	while (count) {
		int x = rand() % row + 1;	//设置雷的随机生成坐标
		int y = rand() % col +1;	//设置雷的随机生成坐标
		if (board[x][y] == '0') {	//布雷条件
			board[x][y] = '1';
			count--;
		}
	}
}


//计算雷	计算并返回（x，y）坐标周围的雷数
int get_mine_count(char mine[ROWS][COLS], int x, int y) {
	return  mine[x - 1][y - 1] + mine[x - 1][y] + mine[x - 1][y + 1] +
			mine[x][y - 1] +	 mine[x][y] +	  mine[x][y + 1] +
			mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] - 9 * 48;
}



//找雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
	int x = 0;
	int y = 0;
	int num = 0;
	while (1) {
		printf("请输入排雷坐标:>\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (mine[x][y] == '1') {				//点到雷
				printf("很遗憾，你被炸死了\n");
				DisplayBoard(mine, row, col);		//展示雷图
				break;
			}
			else {									//没点到雷
				int count = get_mine_count(mine, x, y);
				show[x][y] = count + '0';			//显示周围雷数
				DisplayBoard(show, ROW, COL);		//显示游戏界面
				num++;
			}
		}
		else
			printf("非法输入，请重新输入！！！\n");
		if (num == row * col - EasyCount) {
			printf("恭喜你，游戏通关！！！\n");
			DisplayBoard(mine, row, col);		//展示雷图
			break;
		}
	}
}