#include <stdio.h>

#define row 2	//����������
#define col 3	//����������

int main(){
	int x = 0, y = 0;//������ֵ����
	int max = 0; 	//������ֵ
	int num[row][col] = {0};
	int flag = 0;	//��־λ
	//��������
	printf("������%d�����֣�\n", row * col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			scanf("%d", &num[i][j]);
		}
	}
	//Ѱ�����ֵ
	max = num[0][0];
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(num[i][j] >= max){
				if(num[i][j] == max)
					flag = 1;
				else
					flag = 0;
				max = num[i][j];
				x = i;
				y = j;
				
			}
		}
	}
	//�����ݷ��������д�ӡ����
	printf("���������ַ���һ�� %d * %d �������У�\n", row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%d\t",num[i][j]);
		}
		printf("\n");
	}
	//�ж����ֵ�Ƿ�Ψһ
	if(flag == 0){		//һ�����ֵ
		printf("��������������ֵ�ǣ�%d\n", max);
		printf("���������ǣ�( %d , %d )\n", x + 1, y + 1);
	}
	else{				//������ֵ
		printf("���������ж�����ֵ\n");
		printf("�������������ֵ�ǣ�%d\n", max);
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(num[i][j] == max){
				printf("���������ǣ�( %d , %d )\n", i + 1, j + 1);
				}
		}
	}		
	}
	return 0;
}








