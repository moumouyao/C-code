#include <stdio.h>

void Judge_leap_year(int i);

int main(){
	int y = 0;		//������
	printf("������һ����ݣ�\n");
	while(1){
		scanf("%d", &y);
		if(y >= 0)
			break;
		printf("����Ƿ������������룺\n");
	}
	Judge_leap_year(y);
			
	return 0;
}


/*
	��飺 �ж��Ƿ�Ϊ���꣬����ӡ
	������ int y �������
	����ֵ����
*/
void Judge_leap_year(int i){
	if(i % 400 == 0 || i % 4 == 0 && i % 100 != 0)
		printf("%d������\n", i);
	else
		printf("%d��������\n", i);
}