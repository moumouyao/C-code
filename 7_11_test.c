#include <stdio.h>

int main() {
	//����
	printf("**********************************************\n");
	printf("*******���ֵ*****��Сֵ******ƽ��ֵ**********\n");
	printf("**********************************************\n");
	int arr[32] = { 0 };		//����
	int num = 0;			//���ָ���
	int tmp = 0;			//��ʱ�������
	int sum = 0;			//���
	float everage = 0;		//ƽ��ֵ
	//��ȡ���ָ��������ж��Ƿ�Ϸ�
	while (1) {
		printf("��������Ҫ��ֵ�����ָ���(3 ~ 32)��\n");
		scanf("%d", &num);
		if (num > 2 && num < 33)
			break;
		else
			printf("����Ƿ�������\n");

	}
	//��ȡ����
	printf("������%d������:\n", num);
	for (int i = 0; i < num; i++) {
		scanf("%d", &arr[i]);
		sum = arr[i] + sum;		//���
	}
	everage = (float)sum / num;	//��ƽ��ֵ
	//�����ֵ
	for (int i = 0; i < num - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
		}
	}


	//����Сֵ
	for (int i = num - 2; i >= 0; i--) {
		if (arr[i] < arr[i - 1]) {
			tmp = arr[i];
			arr[i] = arr[i - 1];
			arr[i - 1] = tmp;
		}
	}
	printf("�������ݵ����ֵΪ��%d����СֵΪ��%d��ƽ��ֵΪ%f\n", arr[num - 1], arr[0], everage);
	return 0;
}