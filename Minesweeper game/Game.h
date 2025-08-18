#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
//引入头文件
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//定义棋盘大小
#define ROW  9
#define COL  9
//定义雷的个数
#define EasyCount 3
//隐藏的棋盘
#define ROWS  ROW + 2
#define COLS  ROW + 2

//定义初始化函数
void InitBoard(char board[ROWS][COLS], int rows, int cols , char set);
//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col);
//布雷
void SetMine(char board[ROWS][COLS], int row, int col);
//找雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
