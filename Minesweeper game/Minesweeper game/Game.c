
#include "Game.h"


//���̳�ʼ��	0�����	1������	*��ʾ����
//mine[][]ȫ��0 ��show[][]ȫ��*
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = set;
		}
	}
}

//��ӡ����
void DisplayBoard(char board[ROWS][COLS], int row, int col) {
	
	for (int i = 0; i < 10; i++) {		//��ӡ�к�
		printf("%d ", i);
	}
	printf("\n");

	for (int i = 1; i <= row; i++) {
		printf("%d ", i);		//��ӡ�к�
		for (int j = 1; j <= col; j++) {		//��ӡ��������
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}


//����
void SetMine(char board[ROWS][COLS], int row, int col){

	int count = EasyCount;
	while (count) {
		int x = rand() % row + 1;	//�����׵������������
		int y = rand() % col +1;	//�����׵������������
		if (board[x][y] == '0') {	//��������
			board[x][y] = '1';
			count--;
		}
	}
}


//������	���㲢���أ�x��y��������Χ������
int get_mine_count(char mine[ROWS][COLS], int x, int y) {
	return  mine[x - 1][y - 1] + mine[x - 1][y] + mine[x - 1][y + 1] +
			mine[x][y - 1] +	 mine[x][y] +	  mine[x][y + 1] +
			mine[x + 1][y - 1] + mine[x + 1][y] + mine[x + 1][y + 1] - 9 * 48;
}



//����
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
	int x = 0;
	int y = 0;
	int num = 0;
	while (1) {
		printf("��������������:>\n");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (mine[x][y] == '1') {				//�㵽��
				printf("���ź����㱻ը����\n");
				DisplayBoard(mine, row, col);		//չʾ��ͼ
				break;
			}
			else {									//û�㵽��
				int count = get_mine_count(mine, x, y);
				show[x][y] = count + '0';			//��ʾ��Χ����
				DisplayBoard(show, ROW, COL);		//��ʾ��Ϸ����
				num++;
			}
		}
		else
			printf("�Ƿ����룬���������룡����\n");
		if (num == row * col - EasyCount) {
			printf("��ϲ�㣬��Ϸͨ�أ�����\n");
			DisplayBoard(mine, row, col);		//չʾ��ͼ
			break;
		}
	}
}