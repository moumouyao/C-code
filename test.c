//���������������������ֽ���������������Ҫ������������:1���������������;2������
//���������� �磺 6 = 2 * 3      12 = 2 * 2 * 3
//
#define _CRT_SECURE_NO_WARNINGS  1;
#include <stdio.h>

void achieve(int input) {
	int tmp1 = 0, tmp2 = 0, i = 2;
	if (input < 2) {
		//printf("%d", input);
		return;
	}
	while (1) {
		tmp1 = input / i;
		tmp2 = input % i;
		if (tmp2 != 0)		//�ֽ�
			i++;
		else
			break;
	}
	printf("%d  ", i);
	if (tmp1 > 1)
		printf("* ");

	achieve(tmp1);

}


int main() {
	int input = 0;

	while (1) {			//����һ��������
		printf("������һ����������\n");
		scanf("%d", &input);
		if (input > 0)
			break;
		else
			printf("����Ƿ����������룡����\n");
	}
	printf("%d = ", input);
	achieve(input);

	return 0;
}
