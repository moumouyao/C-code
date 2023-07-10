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
	//����-����߳���������Ϣ
	char board[ROW][COL] = {0};
	//��ʼ������Ϊ�ո�
	InitBoard(board, ROW, COL);
	//��ӡ����
	DisplayBoard(board, ROW, COL);
	//����
	while (1) {
		//�������
		PlayerMove(board, ROW, COL);
		num++;//������ռ�õ����̸���
		DisplayBoard(board, ROW, COL);
	
		//�ж���Ӯ
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;

		//��������
		ComputerMove(board, ROW, COL);
		num++;
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;

	}
	if (ret == '*')
		printf("���Ӯ\n");
	else if (ret == '#')
		printf("����Ӯ\n");
	else
		printf("ƽ��\n");
}

void test() {

	int input = 0;

	do {
		menu();
		printf("������ָ�� ��\n");
		scanf("%d", &input);
		switch (input) {
		case 1:
			printf("������\n");
			game();
			break;
		case 0:
			printf("��Ϸ�˳�\n");
			break;
		default :
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);

}

int main() {


	test();
	return 0;
}