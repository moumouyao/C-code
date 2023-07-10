#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

extern int num;	//����ȫ�ֱ���


//��ʼ��
void InitBoard(char board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board[i][j] = ' ';
		}
	}
}


//��ӡ����
void DisplayBoard(char board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {

	
		//��ӡһ������
		for (int j = 0; j < col; j++) {
			printf(" %c ", board[i][j]);	//�ȴ�ӡ����
			if (j < col - 1)		//���һ�в���ӡ�ָ���
				printf("|");
			if (j == col - 1)	//�������һ�����Ӵ�ӡ֮����
				printf("\n");
		}
		//��ӡ�ָ���
		if (i < row - 1) {		//���һ�в���ӡ�ָ���
			for (int m = 0; m < col; m++) {
				printf("---");		//��ӡ�ָ���
				if (m < col - 1)	//���һ�в���ӡ�ָ���
					printf("|");
				if (m == col - 1)	//�������һ���ָ��ߴ�ӡ֮����
					printf("\n");
			}
		}
	}
}


//�������
void PlayerMove(char board[ROW][COL], int row, int col) {

	int x = 0, y = 0;
	printf("�����:>\n");
	while (1) {
		printf("������Ҫ�µ�����\n");
		scanf("%d%d", &x, &y);
		//�ж��������ĺϷ���
		if ((x <= row && x >= 1) && (y <= col && y >= 1) && (board[x - 1][y - 1] == ' ')) {
			board[x - 1][y - 1] = '*';
			break;
		}
		else
			printf("�Ƿ�λ�ã�����������!\n");
	}

}


//��������
void ComputerMove(char board[ROW][COL], int row, int col) {
	int x = 0, y = 0;
	printf("������:>\n");
	//�жϵ�������λ�õĺϷ���
	while (1) {
		srand((unsigned int)time(NULL));	//��ʼ���������
		x = rand() % row;		//���0��row-1��һ�������
		y = rand() % col;		////���0��col-1��һ�������
		if ((x <= row - 1 && x >= 0) && (y <= col - 1 && y >= 0) && (board[x][y] == ' ')) {
			board[x][y] = '#';
			break;
		}
	}
}


//�ж���Ӯ
//		*		���Ӯ
//		#		����Ӯ
//		Q		ƽ��
//		C		����
char IsWin(char board[ROW][COL], int row, int col) {
	//������
	for (int i = 0; i < row; i++) {		//����Ԫ������Ҳ����ڿո�
		if (board[i][0] == board[i][1] && board[i][2] == board[i][0] && board[i][0] != ' ')
			return board[i][0];
	}
	//������
	for (int i = 0; i < col; i++) {		//����Ԫ������Ҳ����ڿո�
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ')
			return board[0][i];
	}
	//б����	//����Ԫ������Ҳ����ڿո�
	if (board[1][1] == board[2][2] && board[1][1] == board[0][0] && board[1][1] != ' ')
		return board[1][1];	//����Ԫ������Ҳ����ڿո�
	if (board[1][1] == board[2][0] && board[1][1] == board[0][2] && board[1][1] != ' ')
		return board[1][1];
	if (num == 9)	//���鱻����
		return 'Q';
	
	return 'C';
}