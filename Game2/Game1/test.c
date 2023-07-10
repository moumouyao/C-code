#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include "game.h"

int num = 0;


void menu() {
	printf("*************************************************\n");
	printf("**********   1 . play       0 . exit   **********\n");
	printf("*************************************************\n");
}

void game() {
	char ret = 0;
	 num = 0;
	//数组-存放走出的棋盘信息
	char board[ROW][COL] = {0};
	//初始化棋盘为空格
	InitBoard(board, ROW, COL);
	//打印棋盘
	DisplayBoard(board, ROW, COL);
	//下棋
	while (1) {
		//玩家下棋
		PlayerMove(board, ROW, COL);
		num++;//计算所占用的棋盘格数
		DisplayBoard(board, ROW, COL);
	
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;

		//电脑下棋
		ComputerMove(board, ROW, COL);
		num++;
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;

	}
	if (ret == '*')
		printf("玩家赢\n");
	else if (ret == '#')
		printf("电脑赢\n");
	else
		printf("平局\n");
}

void test() {

	int input = 0;

	do {
		menu();
		printf("请输入指令 ：\n");
		scanf("%d", &input);
		switch (input) {
		case 1:
			printf("三子棋\n");
			game();
			break;
		case 0:
			printf("游戏退出\n");
			break;
		default :
			printf("选择错误，请重新选择！\n");
			break;
		}
	} while (input);

}

int main() {


	test();
	return 0;
}