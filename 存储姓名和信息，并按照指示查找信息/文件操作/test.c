#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
//
//int main() {
//	
//	FILE* fp = fopen("1.txt", "w+");
//	int ret = 0;
//	if (fp == NULL) {
//		perror(fopen);
//		return EOF;
//	}
//	else {
//		printf("�ļ������ɹ�\n");
//	}
//	ret = fputc('S', fp);
//	if (ret == EOF) {
//		perror(fputc);
//		return EOF;
//	}
//	else {
//		printf("�ַ��洢�ɹ�\n");
//	}
//	rewind(fp);
//	ret = fgetc(fp);
//	if (ret == EOF) {
//		perror(fgetc);
//		return EOF;
//	}
//	else {
//		printf("%c\n", (char)ret);
//		printf("��ӡ�ɹ�\n");
//	}
//	fclose(fp);
//	fp = NULL;
//	return 0;
//}
//
//int main() {
//	char name[20] = { 0 };
//	char address[128] = { 0 };
//	FILE* fp = fopen("2.txt", "w+");
//	if (fp == NULL) {
//		perror(fopen);
//		return EOF;
//	}
//	else {
//		printf("�ļ������ɹ�\n");
//	}
//	printf("����������\n");
//	scanf("%s", name);
//	if (fputs(name, fp) == EOF) {
//		perror(fputs);
//		return EOF;
//	}
//	else {
//		printf("����¼��ɹ�\n");
//	}
//	printf("�������ַ\n");
//	scanf("%s", address);
//	if (fputs(address, fp) == EOF) {
//		perror(fputs);
//		return EOF;
//	}
//	else {
//		printf("��ַ¼��ɹ�\n");
//	}
//
//	fclose(fp);
//	fp = NULL;
//	
//	return 0;
//}
//
//int main() {
//	int j = 0;
//	 FILE* fp = fopen("4.txt", "w+");
//	 char n[8] = { 0 };
//	 fputs("2\t", fp);
//	 fputs("3\t", fp);
//	 fputs("5\t", fp);
//	 for (int i = 2; i < 200; i++) {
//		 if (i % 2 == 0 || i % 5 == 0) {
//			 continue;
//		 }
//		 for ( j = 2; j < i / 2; j++) {
//			 if (i % j == 0) {
//				 
//				 break;
//			 }
//		 }
//		 if (j == i / 2 ) {
//			 fprintf(fp, "%d\t", i);
//		 }
//	 }
//	 fclose(fp);
//	 fp = NULL;
//	return 0;
//}
//
void clear();
void clearS();

int main() {

	
	int n = 0;
	int i = 0;
	FILE* fp = NULL;
	FILE* ftp = NULL;
	char name[24] = { 0 };
	char address[128] = { 0 };
	char fname[24] = { 0 };
	char faddress[128] = { 0 };
	//ѡ����
	while (1) {
		while (1) {
			printf("�� 1 ¼����Ϣ\n");
			printf("�� 2 ��Ϣ��ѯ\n");
			printf("�� 3 �鿴������Ϣ\n");
			printf("�� 4 ɾ����Ϣ\n");
			printf("�������˳�����\n");
			scanf("%d", &n);
			clear();
			if (n != 1 && n != 2 && n != 3 && n != 4) {
				clearS();
				printf("�����˳�\n");
				return -1;
			}
			else {
				clearS();
				break;
			}
		}

		switch (n) {
		case 1: {
			fp = fopen("2.txt", "a");
			if (fp == NULL) {
				perror(fopen);
			}
			printf("����������\n");
			scanf("%s", name);
			clear();
			n = fprintf(fp, "%s\t", name);
			if (n == EOF) {
				perror(fprintf);
			}
			clearS();
			printf("������סַ\n");
			scanf("%s", address);
			clear();
			n = fprintf(fp, "%s\n", address);
			if (n == EOF) {
				perror(fprintf);
			}

			fclose(fp);
			fp = NULL;
			break;
		}
		case 2: {
			fp = fopen("2.txt", "r");
			printf("��ѡ���ѯ��ʽ\n");
			printf("1.��������ѯ\n");
			printf("2.����ַ��ѯ\n");
			printf("���������˳�\n");
			scanf("%d", &n);
			clear();
			switch (n) {
			case 1: {
				printf("��������Ҫ��ѯ������\n");
				scanf("%s", name);
				clear();
				clearS();
				while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
					if (strcmp(name, fname) == 0) {
						printf("������%s\t��ַ��%s\n", fname, faddress);
					}
				}
				break;
			}
			case 2: {
				printf("��������Ҫ��ѯ�ĵ�ַ\n");
				scanf("%s", address);
				clear();
				clearS();
				while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
					if (strcmp(address, faddress) == 0) {
						printf("������%s\t��ַ��%s\n", fname, faddress);
					}
				}
				break;
			}
			}
			fclose(fp);
			break;
		}
		case 3: {
			i = 0;
			fp = fopen("2.txt", "r");
			while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
					printf("������%s\t��ַ��%s\n", fname, faddress);
					i++;
			}
			if (i == 0) {
				printf("����¼����Ϣ\n");
				fclose(fp);
				break;
			}
			fclose(fp);
			break;
		}
		case 4: {
			i = 0;
			fp = fopen("2.txt", "r");
			ftp = fopen("tmp.txt", "w+");
			while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
				i++;
				printf("%d\t", i);
			
				printf("������%s\t��ַ��%s\n", fname, faddress);

			}
			printf("������Ҫɾ���ı��(����ֵ�˳�)\n");
			scanf("%d", &n);
			clear();
		
			if (n > i) {
				printf("����¼����Ϣ\n");
				fclose(fp);
				fclose(ftp);
				break;
			}
			rewind(fp);
			i = 1;
			while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
				
				if (n != i) {
					//printf("������%s\t��ַ��%s\n", fname, faddress);
					fprintf(ftp, "%s\t%s\n", fname, faddress);
				}
				i++;
			}
			fclose(fp);
			fclose(ftp);
			remove("2.txt");
			rename("tmp.txt", "2.txt");
			printf("ɾ���ɹ�\n");

			break;
		}
		}
	}
	



	return 0;
}

//��������
void clear() {
	while (getchar() != '\n');
}

//����
void clearS() {
	printf("\033[2J\033[1;1H");
}

//
//int main() {
//	int n[64] = { 0 };
//	int j = 0;
//	int k = 0;
//	FILE* fp = fopen("5.txt", "w");
//	for (int i = 0; i <= 15; i++) {
//		j = i;
//		k = 0;
//		memset(n, 0, sizeof(n));
//		while (j) {
//			n[k] = j % 2;
//			j = j / 2;
//			k++;
//
//		}
//		fprintf(fp, "%d\t", i);
//		for (int i = k - 1; i >=0; i--) {
//			fprintf(fp, "%d\t", n[i]);
//		}
//		fprintf(fp, "\n");
//		
//	}
//	fclose(fp);
//	fp = NULL;
//	return 0;
//}