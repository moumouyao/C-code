#include <stdio.h>

#define length 5 //�������鳤��

float Average_Value(float* input, int len);

int main(){
		float input[length] = {0};	//��Ŷ��������
		float a = 0;		//���ƽ��ֵ
		printf("������%d�����ݣ�\n", length);
		for(int i = 0; i < length; i ++){	//��������
			printf("�������%d�����ݣ�\n", i + 1);
			scanf("%f", &input[i]);
		}
		a = Average_Value(input, length);	//��ƽ��ֵ
		printf("��%d�����ݵ�ƽ��ֵ��%.2f\n", length, a);
	return 0;
}


/*
	��飺���������
	������float* input �����׵�ַ	int length ���鳤��
	����ֵ��sum / length ƽ��ֵ
*/
float Average_Value(float* input, int len){
			float sum = 0;
			for(int i = 0; i < length; i++){
				sum = sum + *(input + i);
			}
			return sum / length;
}
