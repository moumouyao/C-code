#include <stdio.h>

#define row 3	//����������
#define col 3	//S����������


int main(){
	int num1[row][col] = {0};	//���ԭ����
	int num2[col][row] = {0};	//���ת�ú������
	
	//��������
	printf("������%d�����֣�\n", row * col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%d", &num1[i][j]);
		}
	}
	//�Ծ������ת��
	for(int i = 0; i < row; i++){	
		for(int j = 0; j < col; j++){	
			num2[j][i] = num1[i][j];
		}
	}

	//��ӡԭ����
	printf("���������ַ���һ�� %d * %d �ľ����У�\n", row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num1[i][j]);
		}
		printf("\n");
	}
	//��ӡת�ú�ľ���
	printf("ת�ú�ľ���\n");
	for(int i = 0; i < col; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num2[i][j]);
		}
		printf("\n");
	}
		
		
		
	
	return 0;
}








