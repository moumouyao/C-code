
#include <stdio.h>

#define row 3	//����������
#define col 4	//����������


int main() {
	int num[row][col] = { 0 };	//���ԭ����
	int all[col] = { 0 };			//����ܳɼ�
	float eve1[col] = { 0 };		//��Ÿ���ƽ���ɼ�
	float eve2[row] = { 0 };		//���ÿ��ͬѧ��ƽ���ɼ�
	float tmp = 0;				//�����ʱ����
	int c = 0;					//


	//����ɼ�
	for (int i = 0; i < row; i++) {
		printf("�������%dλͬѧ��%d�Ƴɼ�\n", (i + 1), col);
		for (int j = 0; j < col; j++) {
			printf("�������%d�Ƴɼ�:\n", (j + 1));
			scanf("%d", &num[i][j]);
		}
	}
	//
	for (int i = 0; i < row; i++) {
		tmp = 0;
		for (int j = 0; j < col; j++) {
			tmp = num[i][j] + tmp;		//��ÿ��ͬѧ�ܳɼ�
		}
		all[i] = tmp;
		eve2[i] = all[i] / (float)col;		//��ÿ��ͬѧ����ƽ���ɼ�
	}
	//�����ƽ���ɼ�
	for (int j = 0; j < col; j++) {
		tmp = 0;
		for (int i = 0; i < row; i++) {
			tmp = num[i][j] + tmp;		//�����ܳɼ�
		}
		eve1[j] = tmp / row;		//����ƽ���ɼ�
	}
	//�����ƽ���ɼ�
	for (int i = 0; i < row; i++) {
		printf("��%dλͬѧ�ĸ��Ƴɼ���\t", i + 1);
		for (int j = 0; j < col; j++) {
			printf("%d\t", num[i][j]);
		}
		printf("\n");
	}
	//��ӡ��߳ɼ�
	tmp = all[0];
	for (int i = 0; i < row - 1; i++) {
		if (all[i] > tmp) {
			tmp = all[i];
			c = i;
		}


	}
	printf("\n");
	//��ӡ��߳ɼ�
	printf("��%dλ���ܳɼ������%.1f\n", c + 1, tmp);
	printf("\n");

	//��ӡ����ƽ���ɼ�
	for (int i = 0; i < col; i++) {
		printf("��%d�Ƶ�ƽ���ɼ�Ϊ%.1f\n", i + 1, eve1[i]);
	}
	printf("\n");
	//��ӡÿ��ͬѧƽ���ɼ�
	for (int i = 0; i < row; i++) {
		printf("��%dλͬѧ��ƽ���ɼ�Ϊ%.1f\n", i + 1, eve2[i]);
	}





	return 0;