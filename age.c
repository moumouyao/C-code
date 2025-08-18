
#include <stdio.h>

int age(int m, int n, int j);

int main() {
	int m, n, j;
	printf("请输入人数：\n");
	scanf("%d", &m);
	getchar();
	printf("请输入第一个人的年龄：\n");
	scanf("%d", &n);
	getchar();
	printf("请输入每个人之间的年龄差：\n");
	scanf("%d", &j);
	getchar();
	printf("最后一个人的年龄为：%d\n", age(m, n, j));
	return 0;
}

int age(int m, int n, int j) {

	if (m == 1) {
		return n;
	}
	else
		return age(m - 1, n, j) + j;
}








