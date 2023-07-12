#define _CRT_SECURE_NO_WARNINGS 1

#include "Game.h"
void menu() {
	printf("***********************************************\n");
	printf("*************       1.play        *************\n");
	printf("*************       2.exit        *************\n");
	printf("***********************************************\n");
}

void Game() {
	//�׵���Ϣ�洢
	char mine[ROWS][COLS] = { 0 };
	//�Ų�������׵���Ϣ
	char show[ROWS][COLS] = { 0 };
	//��ʼ�����̺��׵���Ϣ
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//��ӡ����
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//����
	SetMine(mine, ROW, COL);
	//����
	FindMine(mine, show, ROW, COL);

}

void test() {
	srand((unsigned)time(NULL));
	int input = 0;
	do {
		menu();		//��ӡ�˵�
		printf("������ָ��:>\n");
		scanf("%d", &input);
		switch (input) {
		case 1:
			printf("��Ϸ��ʼ��\n");
			Game();		//��Ϸʵ��
			break;
		case 0:
			printf("��Ϸ�˳�\n");
			break;
		default:
			printf("�Ƿ����룬���������룡����\n");
			break;
		}
	} while (input);
}


int main() {
	test();
	return 0;
}