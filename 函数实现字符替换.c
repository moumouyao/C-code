#include <stdio.h>

#define length 20	//�����ַ����鳤��

void Replace(char* arr, char f, char l);

int main(){
	char arr[length] = {0};	//���������ַ���
	char f = 0;		//������ǰ���ַ�
	char l = 0;		//����������ַ�
	//��������
	printf("������һ���ַ���\n");
	scanf("%s", arr);
	getchar();	//����س�
	printf("��������Ҫ���滻�����ַ���\n");
	scanf("%c", &f);
	getchar();	//����س�
	printf("�������滻֮����ַ���\n");
	scanf("%c", &l);
	//��ӡ�ַ���
	printf("�滻֮ǰ���ַ���:\n%s\n", arr);
	Replace(arr, f, l);		//�滻����
	printf("�滻֮����ַ���:\n%s\n", arr);
	return 0;
}



/*
	��飺�ַ�����ĳ���ַ����滻
	������char* arr ָ���ַ�����ָ�룬 char f �滻ǰ���ַ��� char l �滻����ַ�
	����ֵ����
*/
void Replace(char* arr, char f, char l){
	while(*arr){
		if(*arr == f)
			*arr = l;
	arr++;
	}
}





