#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

extern int num;	//调用全局变量


//初始化
void InitBoard(char board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board[i][j] = ' ';
		}
	}
}


//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {

	
		//打印一行数据
		for (int j = 0; j < col; j++) {
			printf(" %c ", board[i][j]);	//先打印棋子
			if (j < col - 1)		//最后一列不打印分割线
				printf("|");
			if (j == col - 1)	//本行最后一个棋子打印之后换行
				printf("\n");
		}
		//打印分割线
		if (i < row - 1) {		//最后一行不打印分割线
			for (int m = 0; m < col; m++) {
				printf("---");		//打印分割线
				if (m < col - 1)	//最后一列不打印分割线
					printf("|");
				if (m == col - 1)	//本行最后一个分割线打印之后换行
					printf("\n");
			}
		}
	}
}


//玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col) {

	int x = 0, y = 0;
	printf("玩家走:>\n");
	while (1) {
		printf("请输入要下的坐标\n");
		scanf("%d%d", &x, &y);
		//判断玩家下棋的合法性
		if ((x <= row && x >= 1) && (y <= col && y >= 1) && (board[x - 1][y - 1] == ' ')) {
			board[x - 1][y - 1] = '*';
			break;
		}
		else
			printf("非法位置，请重新输入!\n");
	}

}


//电脑下棋
void ComputerMove(char board[ROW][COL], int row, int col) {
	int x = 0, y = 0;
	printf("电脑走:>\n");
	//判断电脑下棋位置的合法性
	while (1) {
		srand((unsigned int)time(NULL));	//初始化随机种子
		x = rand() % row;		//获得0到row-1的一个随机数
		y = rand() % col;		////获得0到col-1的一个随机数
		if ((x <= row - 1 && x >= 0) && (y <= col - 1 && y >= 0) && (board[x][y] == ' ')) {
			board[x][y] = '#';
			break;
		}
	}
}


//判断输赢
//		*		玩家赢
//		#		电脑赢
//		Q		平局
//		C		继续
char IsWin(char board[ROW][COL], int row, int col) {
	//横三列
	for (int i = 0; i < row; i++) {		//三个元素相等且不等于空格
		if (board[i][0] == board[i][1] && board[i][2] == board[i][0] && board[i][0] != ' ')
			return board[i][0];
	}
	//竖三列
	for (int i = 0; i < col; i++) {		//三个元素相等且不等于空格
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
			return board[0][i];
	}
	//斜两列	//三个元素相等且不等于空格
	if (board[1][1] == board[2][2] && board[1][1] == board[0][0] && board[1][1] != ' ')
		return board[1][1];	//三个元素相等且不等于空格
	if (board[1][1] == board[2][0] && board[1][1] == board[0][2] && board[1][1] != ' ')
		return board[1][1];
	if (num == 9)	//数组被填满
		return 'Q';
	
	return 'C';
}