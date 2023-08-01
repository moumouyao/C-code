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
//		printf("文件创建成功\n");
//	}
//	ret = fputc('S', fp);
//	if (ret == EOF) {
//		perror(fputc);
//		return EOF;
//	}
//	else {
//		printf("字符存储成功\n");
//	}
//	rewind(fp);
//	ret = fgetc(fp);
//	if (ret == EOF) {
//		perror(fgetc);
//		return EOF;
//	}
//	else {
//		printf("%c\n", (char)ret);
//		printf("打印成功\n");
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
//		printf("文件创建成功\n");
//	}
//	printf("请输入姓名\n");
//	scanf("%s", name);
//	if (fputs(name, fp) == EOF) {
//		perror(fputs);
//		return EOF;
//	}
//	else {
//		printf("姓名录入成功\n");
//	}
//	printf("请输入地址\n");
//	scanf("%s", address);
//	if (fputs(address, fp) == EOF) {
//		perror(fputs);
//		return EOF;
//	}
//	else {
//		printf("地址录入成功\n");
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
	//选择功能
	while (1) {
		while (1) {
			printf("扣 1 录入信息\n");
			printf("扣 2 信息查询\n");
			printf("扣 3 查看所有信息\n");
			printf("扣 4 删除信息\n");
			printf("扣其他退出程序\n");
			scanf("%d", &n);
			clear();
			if (n != 1 && n != 2 && n != 3 && n != 4) {
				clearS();
				printf("程序退出\n");
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
			printf("请输入姓名\n");
			scanf("%s", name);
			clear();
			n = fprintf(fp, "%s\t", name);
			if (n == EOF) {
				perror(fprintf);
			}
			clearS();
			printf("请输入住址\n");
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
			printf("请选择查询方式\n");
			printf("1.按姓名查询\n");
			printf("2.按地址查询\n");
			printf("按其他键退出\n");
			scanf("%d", &n);
			clear();
			switch (n) {
			case 1: {
				printf("请输入想要查询的姓名\n");
				scanf("%s", name);
				clear();
				clearS();
				while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
					if (strcmp(name, fname) == 0) {
						printf("姓名：%s\t地址：%s\n", fname, faddress);
					}
				}
				break;
			}
			case 2: {
				printf("请输入想要查询的地址\n");
				scanf("%s", address);
				clear();
				clearS();
				while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
					if (strcmp(address, faddress) == 0) {
						printf("姓名：%s\t地址：%s\n", fname, faddress);
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
					printf("姓名：%s\t地址：%s\n", fname, faddress);
					i++;
			}
			if (i == 0) {
				printf("请先录入信息\n");
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
			
				printf("姓名：%s\t地址：%s\n", fname, faddress);

			}
			printf("请输入要删除的编号(其他值退出)\n");
			scanf("%d", &n);
			clear();
		
			if (n > i) {
				printf("请先录入信息\n");
				fclose(fp);
				fclose(ftp);
				break;
			}
			rewind(fp);
			i = 1;
			while (fscanf(fp, "%s\t%s\n", fname, faddress) != EOF) {
				
				if (n != i) {
					//printf("姓名：%s\t地址：%s\n", fname, faddress);
					fprintf(ftp, "%s\t%s\n", fname, faddress);
				}
				i++;
			}
			fclose(fp);
			fclose(ftp);
			remove("2.txt");
			rename("tmp.txt", "2.txt");
			printf("删除成功\n");

			break;
		}
		}
	}
	



	return 0;
}

//清理缓冲区
void clear() {
	while (getchar() != '\n');
}

//清屏
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