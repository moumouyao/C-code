#define _CRT_SECURE_NO_WARNINGS 1

#include "Game.h"
void menu() {
	printf("***********************************************\n");
	printf("*************       1.play        *************\n");
	printf("*************       2.exit        *************\n");
	printf("***********************************************\n");
}

void Game() {
	//雷的信息存储
	char mine[ROWS][COLS] = { 0 };
	//排查出来的雷的信息
	char show[ROWS][COLS] = { 0 };
	//初始化棋盘和雷的信息
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//打印棋盘
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//布雷
	SetMine(mine, ROW, COL);
	//找雷
	FindMine(mine, show, ROW, COL);

}

void test() {
	srand((unsigned)time(NULL));
	int input = 0;
	do {
		menu();		//打印菜单
		printf("请输入指令:>\n");
		scanf("%d", &input);
		switch (input) {
		case 1:
			printf("游戏开始！\n");
			Game();		//游戏实现
			break;
		case 0:
			printf("游戏退出\n");
			break;
		default:
			printf("非法输入，请重新输入！！！\n");
			break;
		}
	} while (input);
}


int main() {
	test();
	return 0;
}