#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
//����ͷ�ļ�
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//�������̴�С
#define ROW  9
#define COL  9
//�����׵ĸ���
#define EasyCount 3
//���ص�����
#define ROWS  ROW + 2
#define COLS  ROW + 2

//�����ʼ������
void InitBoard(char board[ROWS][COLS], int rows, int cols , char set);
//��ӡ����
void DisplayBoard(char board[ROWS][COLS], int row, int col);
//����
void SetMine(char board[ROWS][COLS], int row, int col);
//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
