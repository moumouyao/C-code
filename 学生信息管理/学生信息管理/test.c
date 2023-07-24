#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//宏定义
#define length 100	//系统学生容量
#define id_len 2	//id长度
//// 定义汉字编码范围
//#define GB2312_START 0xB0A1 
//#define GB2312_END 0xF7FE
//
//#define GBK_START 0x4E00
//#define GBK_END 0x9FFF 
//
//#define UTF8_START 0x4E00  
//#define UTF8_END 0x9FFF
//
//// 定义编码格式
//#define ENCODING "GB2312"

struct stu {	//声明结构体类型
	int id;
	char name[20];
	char sex[20];
	float score;
};
//全局变量
int count = 0;	//计数器，存放录入学生数量


//函数声明
int my_printf(struct stu stu_info[], int id);
int my_all_printf(struct stu stu_info[]);
int menu();
int get_stu_info(struct stu stu_info[], int id);
int input_stu_info(struct stu stu_info[]);
void change_stu_info(struct stu stu_info[]);
void delete(struct stu stu_info[]);
int* get_stu_name_info(struct stu stu_info[],  char* pn);
int sort_stu_info(struct stu stu_info[], int mode);
int* stu_print(struct stu stu_info[], int mode);
int isChineseString(char* str);
int check_stu_id(int id);
void id_delete(struct stu stu_info[], struct stu d_stu);

int main() {
	int input = 0;	//接收menu()函数返回值
	int mode = 0;	//模式选择
	char ch = 0;	//判断
	struct stu stu_info[length] = { 0 };	//定义结构体数组，用于存储学生信息
	int* re = NULL;		//接收返回地址
	int id = 0;

	do {
		input = menu();

		switch (input) {
		case 1: {		//查询学生信息
			id = 0;
			printf("请输入要查询的学号：\n");
			scanf("%d", &id);
			while ((getchar()) != '\n' ) {}
			id = get_stu_info(stu_info, id);
			if (-1 == id)
				printf("输入学号错误，或该学生不存在\n");
			else
				my_printf(stu_info, id);
			break;
		}

		case 2: {	//录入学生信息
			while (1) {
				id = input_stu_info(stu_info);
				if (id == -3) {
					printf("已取消录入\n");
				}
				else {
					printf("学生信息录入成功\n");
				}
				printf("是否继续录入(y/n):\n");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					break;
			}
			
			break;
		}
		case 3: {	//修改学生信息
			change_stu_info(stu_info);
			break;
		}
		case 4: {	//删除学生信息
			delete(stu_info);
			break;
		}

		case 5: {	//打印所有学生信息
			mode = 0;
			re = NULL;
			while (1) {
				printf("请选择打印模式\n");
				printf("1.按学号升序打印学生信息\n");
				printf("2.按分数段打印打印学生信息\n");
				printf("3.按分数段打印打印学生信息\n");
				printf("4.按性别打印信息\n");
				printf("5.退出\n");
				scanf("%d", &mode);
				while ((getchar()) != '\n') {}
				if (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5) {
					printf("非法输入，请重新输入\n");
				}
				else
					break;
			}
			re = stu_print(stu_info, mode);

			switch (mode) {
			case 1: {
				printf("系统中共有%d人\n", *re);
				printf("按学号排列\n");
				my_all_printf(stu_info);
				printf("打印完成\n");
				break;
			}
			case 2: {
				printf("系统中共有%d人\n", *re);
				printf("按分数排列\n");
				my_all_printf(stu_info);
				printf("打印完成\n");
				break;
			}
			case 3: {
				printf("系统中共有%d在这个分数段\n", *re);
				printf("按分数排列\n");
				for (int i = 1; i < *re + 1; i++) {
					my_printf(stu_info, *(re + i));
				}
				printf("打印完成\n");
				break;
			}
			case 4: {
				printf("系统中共有%d个该性别的同学\n", *re);
				printf("按分数排列\n");
				for (int i = 1; i < *re + 1; i++) {
					my_printf(stu_info, *(re + i));
				}
				printf("打印完成\n");
				break;
			}
			case 5: {

				break;
			}
			}
			
			break;
		}
		case 6: {	//学生信息排序
			 mode = 0;
			while (1) {
				printf("请选择排序方式：\n");
				printf("1.按学号升序排列\n");
				printf("2.按成绩降序排列\n");
				printf("0.退出\n");
				scanf("%d", &mode);
				while ((getchar()) != '\n') {}
				if (mode != 1 && mode != 2) {
					printf("输入错误，请重新输入\n");
				}
				else
					break;
			}
			mode = sort_stu_info(stu_info, mode);
			while (1) {
				printf("排列已完成，是否打印(y/n)：\n");
				scanf("%c", &ch);
				while ((getchar()) != '\n') {}
				if (ch == 'y' || ch == 'Y') {
					if (mode == 1)
						printf("按学号排列\n");
					else if(mode == 2)
						printf("按成绩排列\n");
					my_all_printf(stu_info);
					break;
				}
				else {
					break;
				}
			}
			break;
		}
		}

	} while (input - 7);

	return 0;
}
/*
	功能：打印信息
	参数：struct stu stu_info[], int id
	返回值：无
*/
int my_printf(struct stu stu_info[], int id) {
	if (stu_info[id].id == 0)
		return -1;
	else

	printf("学号：%04d\t 姓名：%-5s\t 性别：%-4s\t 分数：%.2f\n",
		stu_info[id].id, stu_info[id].name, stu_info[id].sex, stu_info[id].score
	);
	return id;
}

/*
	功能：打印所有学生信心
	参数：struct stu stu_info[]	
	返回值：
				0		未打印
				1		打印完成
*/
int my_all_printf(struct stu stu_info[]) {
	if (count == 0) {
		printf("系统中无学生信息\n");
		return 0;
	}
	for (int i = 0; i < count; i++) {
		my_printf(stu_info, i);
		printf("\n");
	}
	return 1;
}

/*
	功能：打印菜单，返回相应的代号
	参数：无
	返回值：	
				0.*************退出信息管理系统
				1.*************查看录入学生信息
				2.*************录入学生信息
				3.*************修改学生信息
				4.*************删除学生信息
				5.*************打印所有学生信息
				6.*************学生信息排序
*/
int menu(){
	while (1) {
		int input = 0;
		printf("**************学生信息管理系统**************\n");
		printf("1.*************查看录入学生信息*************\n");
		printf("2.*************录入学生信息*****************\n");
		printf("3.*************修改学生信息*****************\n");
		printf("4.*************删除学生信息*****************\n");
		printf("5.*************打印所有学生信息*************\n");
		printf("6.*************学生信息排序*****************\n");
		printf("7.*************退出信息管理系统*************\n");
		printf("请输入相应的指令：\n");
		scanf("%d", &input);
		while ((getchar()) != '\n' ) {}
		if (input != 7 && input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6)
			printf("输入错误，请重新输入\n");
		else {
			return input;
			break;
		}
	}
}

/*
	功能：查看录入学生信息
	参数：stu_info 结构体数组	count 学生数量
	返回值：
			-1		未找到
			下标	找到
*/
int get_stu_info(struct stu stu_info[], int id) {

	for (int i = 0; i < count; i++) {	//查找结构体中是否有此学号
		if (id == stu_info[i].id)
			return i;
	}
	return -1;
}

/*
	功能：通过姓名查看录入学生信息
	参数：stu_info 结构体数组	const char* pn	学生姓名
	返回值：mum
			
*/
int* get_stu_name_info(struct stu stu_info[], char* pn) {
 
	static int num[length] = { 0 };
	int n = 1;
	memset(num, 0, sizeof(num));
	for (int i = 0; i < count; i++) {	//查找结构体中是否有此名字
		if (strcmp(pn,stu_info[i].name) == 0) {
			num[n] = i;
			n++;
			num[0]++;
		}
			

	}
	return num;
}

/*
	功能：录入学生信息
	参数：stu_info[]学生结构体	count 计数器
	返回值：
			-3		取消录入
			学号	录入成功
*/
int input_stu_info(struct stu stu_info[]) {
	int id = 0;
	int mode = 0;
	//读入id
	while (1) {
		printf("请创建学生id:\n");
		scanf("%d", &id);
		while ((getchar()) != '\n') {}
		if (-1 != get_stu_info(stu_info, id)) {	//判断id是否合法
			printf("该学号已被占用\n");
			continue;
		}
		else if (id <= 0 || check_stu_id(id) != id_len) {
			printf("请输入 1---%d 范围内的学号\n", length - 1);
			continue;
		}
		else {
			stu_info[count].id = id;
			break;
		}
			
	}

	//读入姓名
	while (1) {
		printf("请输入学生姓名：\n");
		printf("请用中文录入\n");
		scanf("%s", stu_info[count].name);
		while ((getchar()) != '\n') {}
		if (isChineseString(stu_info[count].name) == 0) {
			printf("输入的姓名非纯中文，请重新输入\n");
		}
		else if (isChineseString(stu_info[count].name) == 1) {
			break;
		}
	}

	//读入性别
	while (1) {							
		mode = 0;
		printf("请选择学生性别：\n");
		printf("1.男性\n");
		printf("2.女性\n");
		printf("3.退出\n");
		scanf("%d", &mode);
		while ((getchar()) != '\n') {}
		if (mode != 1 && mode != 2 && mode != 3) {
			printf("非法输入，请重新选择\n");
		}
		else
			break;
	}
	switch (mode) {
	case 1: {
		strncpy(stu_info[count].sex, "男", 15);
		break;
	}
	case 2: {
		strcpy(stu_info[count].sex, "女");
		break;
	}
	case 3: {	//删除
		stu_info[count] = stu_info[count + 1];//置零
		return -3;
	}
	}
	//读入分数
	do {

		printf("请输入学生分数:\n");
		scanf("%f", &stu_info[count].score);
		while ((getchar()) != '\n') {}
		if (stu_info[count].score <= 0 || stu_info[count].score > 1000) {
			printf("分数必须在0-1000之间!\n");
		}
		else {
			break;
		}
	} while (1);
	count++;	//统计录入数量
	return id;
}

/*
	功能：修改学生信息
	参数：stu_info[] 学生结构体		
	返回值：
*/
void change_stu_info(struct stu stu_info[]) {
	int id = 0;		//学号
	char ch = 0;	//判断字符
	int input = 0;	//存放修改信息标志
	struct stu n_stu = {0};	//存放要修改的信息
	while (1) {
		printf("请输入需要修改信息的学生学号:\n");	//读入id并判断是否合法
		scanf("%d", &id);
		while ((getchar()) != '\n' ) {}
		id = get_stu_info(stu_info, id);	//数组下标赋值给id
		if (id == -1) {
			printf("未找到改学生\n");
			printf("是否要从新查找（y/n）");
			scanf("%c", &ch);
			while ((getchar()) != '\n' ) {}
			if (ch == 'y' || ch == 'Y')
				continue;
			else
				break;
		}
		my_printf(stu_info, id);
		do {	//修改信息
			printf("请输入需要修改的信息：\n");
			printf("1.修改学号\n");
			printf("2.修改姓名\n");
			printf("3.修改性别\n");
			printf("4.修改分数\n");
			printf("0.退出\n");
			scanf("%d", &input);
			while ((getchar()) != '\n' ) {}
			switch (input) {
			case 1: {	//修改学号
				printf("请输入新的学号：\n");
				scanf("%d", &n_stu.id);
				while ((getchar()) != '\n' ) {}
				if (n_stu.id <= 0) {
					printf("新的学号非法\n");
					break;
				}
				if (get_stu_info(stu_info, n_stu.id) == -1) {
					stu_info[id].id = n_stu.id;
					printf("修改成功\n");
					my_printf(stu_info, id);
					break;
				}
				else {
					printf("该学号已经被使用\n");
					break;
				}

				}
			case 2: {	//修改姓名
				printf("请输入新的姓名：\n");
				scanf("%s", stu_info[id].name);
				while ((getchar()) != '\n' ) {}
				printf("姓名修改成功\n");
				my_printf(stu_info, id);
				break;
			}
			case 3: {	//修改性别
				printf("请输入新的性别：\n");
				scanf("%s", stu_info[id].sex);
				printf("性别修改成功\n");
				my_printf(stu_info, id);
				break;
			}
			case 4: {	//修改分数
				printf("请输入新的分数:\n");
				scanf("%f", &stu_info[id].score);
				printf("分数修改成功\n");
				my_printf(stu_info, id);
				break;
			}
			}

		} while (input);
		printf("是否继续修改学生信息（y/n）：\n");
		scanf("%c", &ch);
		if (ch == 'y' || ch == 'Y')
			continue;
		else
			break;

	}


	


}

/*
	功能：删除学生信息
	参数：
	返回值：
*/
void delete(struct stu stu_info[]) {
	int n = 0;	//查询方式标识
	char ch = 0;	//退出标识
	struct stu d_stu = { 0 };	//存放需要删除的学生信息
	int* num = NULL;
	int j = 1;		//给序号
	int m = 0;	//接返回值
	do {
		while (1) {
			printf("请输入需要删除的学生信息:\n");
			printf("1.按学号查找\n");
			printf("2.按姓名查找\n");
			printf("0.退出\n");
			scanf("%d", &n);
			while ((getchar()) != '\n' ) {}
			if (n != 1 && n != 2 && n != 0) {
				printf("指令错误，请重新输入\n");
			}
			else {
				break;
			}
		}
		switch (n) {
		case 2: {	//按姓名查找
			printf("请输入需要删除学生的姓名：\n");
			scanf("%s", d_stu.name);
			while ((getchar()) != '\n') {}
			num = get_stu_name_info(stu_info, d_stu.name);	//获取数组下表
			if (*num == 0) {							//输入学号错误
				printf("姓名输入错误或该学生不存在\n");
				printf("是否重新输入（y/n）：\n");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					break;
			}
			else {			////输入学号正确
					j = 1;
					for (int i = 1; i <= *num; i++) {
						/*if (m != -1 && i < *num) {
							printf("%d.\t", j++);
						}*/
						m = my_printf(stu_info, *(num + i));	//打印相同姓名的学生

					}


			}


		}
		case 1: {	//按学号查找
			while (1) {
				printf("请输入需要删除学生的学号：\n");
				scanf("%d", &d_stu.id);
				while ((getchar()) != '\n' ) {}
				d_stu.id = get_stu_info(stu_info, d_stu.id);	//获取数组下表
				if (d_stu.id == -1) {							//输入学号错误
					printf("输入学号错误或该学号不存在\n");
					printf("是否重新输入（y/n）：\n");
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')
						continue;
					else										
						break;
				}
				else {			////输入学号正确
					id_delete(stu_info, d_stu);	//根据学号删除学号删除
						printf("删除完毕，是否继续删除（y/n）：");
						scanf("%c", &ch);
						if (ch == 'y' || ch == 'Y')
							continue;
						else
							break;
				}	
			}
			break;
		}

		}

	} while (n);

}

/*
	功能：按学号或分数排序
	参数：struct stu stu_info[] 学生信息数组, int mode 排序模式
	返回值：
			1	学号排列
			2	成绩
			0	输入错误
*/
int sort_stu_info(struct stu stu_info[], int mode) {

	struct stu t_stu = { 0 };
	char ch = 0;	//接收用户输入
	if (mode == 1) {

		printf("按学号升序排列：\n");
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {

				if (stu_info[j].id > stu_info[j + 1].id) {
					t_stu = stu_info[j];
					stu_info[j] = stu_info[j + 1];
					stu_info[j + 1] = t_stu;
				}
			}
		}
		return 1;
	}
	else if (mode == 2) {
		printf("按成绩降序排列：\n");
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {

				if (stu_info[j].score < stu_info[j + 1].score) {
					t_stu = stu_info[j];
					stu_info[j] = stu_info[j + 1];
					stu_info[j + 1] = t_stu;
				}
			}
		}
		return 2;
	}
	else
		return 0;
}

/*
	功能：打印学生信息
	参数：
	返回值：
				1		按学号升序打印学生信息
				2		按成绩降序打印学生信息
				3		按分数段打印打印学生信息
				4		按性别打印信息
*/
int* stu_print(struct stu stu_info[], int mode) {
	float beg_sco = 0;	//读入起始分数线
	float end_sco = 0;	//读入截至分数线
	float sbeg_sco = 0;	//学生起始分数线
	float send_sco = 0;	//学生截至分数线
	float score[length] = { 0 };	//存放符合条件的结构体数组下标
	//score[0]存放数量
	static int n[length] = { 0 };		//存放符合条件的结构体数组下标，n[0]存放数量
	int j = 1;			//计数或判断
	switch (mode) {
	case 1: {	//按学号升序打印学生信息
		memset(n, 0, sizeof(n));
		sort_stu_info(stu_info, 1);
		n[0] = count;
		return n;
		break;
	}
	case 2: {	//按成绩降序打印学生信息
		memset(n, 0, sizeof(n));
		sort_stu_info(stu_info, 2);
		n[0] = count;
		return n;
		break;
	}
	case 3: {	//按分数段打印打印学生信息
		//获得所有学生成绩区间
		sort_stu_info(stu_info, 2);
		sbeg_sco = stu_info[count - 1].score;
		send_sco = stu_info[0].score;
		//读入区间并判断是否合法
		while (1) {
			printf("学生的成绩区间为：%f ---- %f\n", sbeg_sco, send_sco);
			printf("请输入起始分数线\n");
			scanf("%f", &beg_sco);
			while ((getchar()) != '\n') {}
			printf("请输入截至分数线\n");
			scanf("%f", &end_sco);
			while ((getchar()) != '\n') {}
			if (beg_sco < sbeg_sco || beg_sco > send_sco || end_sco < sbeg_sco || end_sco > send_sco || beg_sco > end_sco) {
				printf("成绩区间非法，请重新输入\n");
			}
			else
				break;
		}
		//查找
		memset(n, 0, sizeof(n));
		for (int i = 0; i < count; i++) {
			if (stu_info[i].score <= end_sco && stu_info[i].score >= beg_sco) {
				n[j] = i;
				n[0]++;
				j++;
			}
		}
		return n;
		break;
	}
	case 4: {	//按性别打印信息
		while (1) {
			printf("请输入需要打印的性别编号：\n");
			printf("1.打印所有男生\n");
			printf("2.打印所有女生\n");
			printf("3.退出\n");
			scanf("%d", &j);
			while ((getchar()) != '\n') {}
			if (j != 1 && j != 2 && j != 3) {
				printf("非法输入，请重新输入\n");
			}
			else
				break;
		}
		//查找
		memset(n, 0, sizeof(n));
		if (j == 1) {
			for (int i = 0; i < count; i++) {
				if (strcmp(stu_info[i].sex, "男") == 0) {
					n[j] = i;
					n[0]++;
					j++;
				}
			}
		}
		else if (j == 2) {
			for (int i = 0; i < count; i++) {
				if (strcmp(stu_info[i].sex, "女") == 0) {
					n[j] = i;
					n[0]++;
					j++;
				}
			}
		}
		return n;
	}
		  break;
	}



}

/*
	功能：判断字符串是否全为中文
	参数：char* str	字符串首地址
	返回值：
				0	非纯中文
				1	纯中文
*/
// 判断中文字符
//int isChineseChar(short c) {
//	if (ENCODING == "GB2312") {
//		return c >= GB2312_START && c <= GB2312_END;
//	}
//	else if (ENCODING == "GBK") {
//		return c >= GBK_START && c <= GBK_END;
//	}
//	else if (ENCODING == "UTF-8") {
//		return c >= UTF8_START && c <= UTF8_END;
//	}
//}

// 判断字符串是否全为中文
int isChineseString(char* str) {
	//char* p = str;
	//while (*str != '\0') {
	//	short ch = *(short*)p; // 取两个字节
	//		
	//	
	//	if (!isChineseChar(ch)) {
	//		return 0;
	//	}
	//	str = str + 3;
	//}
	//return 1;
	while (*str != '\0') {


		if (!(*str > 127 || *str < 0)) {
			return 0;
		}
		str = str + 1;
	}
	return 1;
}

/*
	功能：计算学号位数
	参数：int id
	返回值
		dig		不等返回输入学号位数
		id_len	相等返回规定位数
*/
int check_stu_id(int id) {

	int dig = 0;

	// 计算学号总位数
	while (id > 0) {
		dig++;
		id /= 10;
	}

	// 和要求长度校验
	if (dig < id_len) {
		return id_len;
	}
	else {
		return dig;
	}

}

/*
	功能：根据学号删除学生信息
	参数：struct stu stu_info[] 学生信息结构体组, struct stu d_stu 存放需要删除的学生信息
	返回值：无
*/
void id_delete(struct stu stu_info[], struct stu d_stu) {
	if (count == 1 || count - 1 == d_stu.id) {
		stu_info[count - 1].id = 0;
		memset(stu_info[count - 1].name, 0, sizeof(stu_info[count - 1].name));
		memset(stu_info[count - 1].sex, 0, sizeof(stu_info[count - 1].sex));
		stu_info[count - 1].score = 0;
		count--;
	}
	else {
		stu_info[d_stu.id] = stu_info[count - 1];	//最后一名学生的信息覆盖需要删除的学生，达到删除效果
		stu_info[count - 1].id = 0;
		memset(stu_info[count - 1].name, 0, sizeof(stu_info[count - 1].name));
		memset(stu_info[count - 1].sex, 0, sizeof(stu_info[count - 1].sex));
		stu_info[count - 1].score = 0;
		count--;
	}
}