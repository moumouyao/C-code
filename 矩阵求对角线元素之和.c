#include <stdio.h>

#define row 3	//����������


int main(){
	int sum = 0; 	//��ŶԽ���Ԫ�غ�
	int num[row][row] = {0};
	//��������
	printf("������%d�����֣�\n", row * row);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			scanf("%d", &num[i][j]);
		}
	}
	//��Խ���Ԫ�غ�
	for(int i = 0; i < row; i++){	//���Խ������
		sum = num[i][i] + sum;
	}
	for(int i = 0; i < row; i++){	//���Խ������
	sum = num[i][row - i -1] + sum;
	}
	//�����ݷ��������д�ӡ����
	printf("���������ַ���һ�� %d * %d �ľ����У�\n", row, row);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < row; j++){
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
		//��ӡ�Խ���Ԫ�غ�	
		printf("�������ĶԽ���Ԫ�غ��ǣ�%d\n", sum);
		
	
	return 0;
}








