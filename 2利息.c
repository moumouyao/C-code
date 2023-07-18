#include <stdio.h>
#include <string.h>
float Interest(float cap, int year, float ins);
int main(){
	float cap = 0;	//存放本金
	int year = 0;	//年数
	float ins = 0;	//利息
	float earn = 0;	//收益
	printf("请输入本金：\n");
	scanf("%f", &cap);
	getchar();
	printf("请输入存款年数：\n");
	scanf("%d", &year);
	getchar();
	printf("请输入每年利息：\n");
	scanf("%f", &ins);
	getchar();
	earn = Interest(cap, year, ins + 1);
	printf("本息和为：\n%f\n", earn);
	return 0;
}




float Interest(float cap, int year, float ins){
		
		if(year-- > 1){
			cap = Interest(cap, year, ins);
			
		}
		return cap * ins;
	}
