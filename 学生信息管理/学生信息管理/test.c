#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//�궨��
#define length 100	//ϵͳѧ������
#define id_len 2	//id����
//// ���庺�ֱ��뷶Χ
//#define GB2312_START 0xB0A1 
//#define GB2312_END 0xF7FE
//
//#define GBK_START 0x4E00
//#define GBK_END 0x9FFF 
//
//#define UTF8_START 0x4E00  
//#define UTF8_END 0x9FFF
//
//// ��������ʽ
//#define ENCODING "GB2312"

struct stu {	//�����ṹ������
	int id;
	char name[20];
	char sex[20];
	float score;
};
//ȫ�ֱ���
int count = 0;	//�����������¼��ѧ������


//��������
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
	int input = 0;	//����menu()��������ֵ
	int mode = 0;	//ģʽѡ��
	char ch = 0;	//�ж�
	struct stu stu_info[length] = { 0 };	//����ṹ�����飬���ڴ洢ѧ����Ϣ
	int* re = NULL;		//���շ��ص�ַ
	int id = 0;

	do {
		input = menu();

		switch (input) {
		case 1: {		//��ѯѧ����Ϣ
			id = 0;
			printf("������Ҫ��ѯ��ѧ�ţ�\n");
			scanf("%d", &id);
			while ((getchar()) != '\n' ) {}
			id = get_stu_info(stu_info, id);
			if (-1 == id)
				printf("����ѧ�Ŵ��󣬻��ѧ��������\n");
			else
				my_printf(stu_info, id);
			break;
		}

		case 2: {	//¼��ѧ����Ϣ
			while (1) {
				id = input_stu_info(stu_info);
				if (id == -3) {
					printf("��ȡ��¼��\n");
				}
				else {
					printf("ѧ����Ϣ¼��ɹ�\n");
				}
				printf("�Ƿ����¼��(y/n):\n");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					break;
			}
			
			break;
		}
		case 3: {	//�޸�ѧ����Ϣ
			change_stu_info(stu_info);
			break;
		}
		case 4: {	//ɾ��ѧ����Ϣ
			delete(stu_info);
			break;
		}

		case 5: {	//��ӡ����ѧ����Ϣ
			mode = 0;
			re = NULL;
			while (1) {
				printf("��ѡ���ӡģʽ\n");
				printf("1.��ѧ�������ӡѧ����Ϣ\n");
				printf("2.�������δ�ӡ��ӡѧ����Ϣ\n");
				printf("3.�������δ�ӡ��ӡѧ����Ϣ\n");
				printf("4.���Ա��ӡ��Ϣ\n");
				printf("5.�˳�\n");
				scanf("%d", &mode);
				while ((getchar()) != '\n') {}
				if (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5) {
					printf("�Ƿ����룬����������\n");
				}
				else
					break;
			}
			re = stu_print(stu_info, mode);

			switch (mode) {
			case 1: {
				printf("ϵͳ�й���%d��\n", *re);
				printf("��ѧ������\n");
				my_all_printf(stu_info);
				printf("��ӡ���\n");
				break;
			}
			case 2: {
				printf("ϵͳ�й���%d��\n", *re);
				printf("����������\n");
				my_all_printf(stu_info);
				printf("��ӡ���\n");
				break;
			}
			case 3: {
				printf("ϵͳ�й���%d�����������\n", *re);
				printf("����������\n");
				for (int i = 1; i < *re + 1; i++) {
					my_printf(stu_info, *(re + i));
				}
				printf("��ӡ���\n");
				break;
			}
			case 4: {
				printf("ϵͳ�й���%d�����Ա��ͬѧ\n", *re);
				printf("����������\n");
				for (int i = 1; i < *re + 1; i++) {
					my_printf(stu_info, *(re + i));
				}
				printf("��ӡ���\n");
				break;
			}
			case 5: {

				break;
			}
			}
			
			break;
		}
		case 6: {	//ѧ����Ϣ����
			 mode = 0;
			while (1) {
				printf("��ѡ������ʽ��\n");
				printf("1.��ѧ����������\n");
				printf("2.���ɼ���������\n");
				printf("0.�˳�\n");
				scanf("%d", &mode);
				while ((getchar()) != '\n') {}
				if (mode != 1 && mode != 2) {
					printf("�����������������\n");
				}
				else
					break;
			}
			mode = sort_stu_info(stu_info, mode);
			while (1) {
				printf("��������ɣ��Ƿ��ӡ(y/n)��\n");
				scanf("%c", &ch);
				while ((getchar()) != '\n') {}
				if (ch == 'y' || ch == 'Y') {
					if (mode == 1)
						printf("��ѧ������\n");
					else if(mode == 2)
						printf("���ɼ�����\n");
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
	���ܣ���ӡ��Ϣ
	������struct stu stu_info[], int id
	����ֵ����
*/
int my_printf(struct stu stu_info[], int id) {
	if (stu_info[id].id == 0)
		return -1;
	else

	printf("ѧ�ţ�%04d\t ������%-5s\t �Ա�%-4s\t ������%.2f\n",
		stu_info[id].id, stu_info[id].name, stu_info[id].sex, stu_info[id].score
	);
	return id;
}

/*
	���ܣ���ӡ����ѧ������
	������struct stu stu_info[]	
	����ֵ��
				0		δ��ӡ
				1		��ӡ���
*/
int my_all_printf(struct stu stu_info[]) {
	if (count == 0) {
		printf("ϵͳ����ѧ����Ϣ\n");
		return 0;
	}
	for (int i = 0; i < count; i++) {
		my_printf(stu_info, i);
		printf("\n");
	}
	return 1;
}

/*
	���ܣ���ӡ�˵���������Ӧ�Ĵ���
	��������
	����ֵ��	
				0.*************�˳���Ϣ����ϵͳ
				1.*************�鿴¼��ѧ����Ϣ
				2.*************¼��ѧ����Ϣ
				3.*************�޸�ѧ����Ϣ
				4.*************ɾ��ѧ����Ϣ
				5.*************��ӡ����ѧ����Ϣ
				6.*************ѧ����Ϣ����
*/
int menu(){
	while (1) {
		int input = 0;
		printf("**************ѧ����Ϣ����ϵͳ**************\n");
		printf("1.*************�鿴¼��ѧ����Ϣ*************\n");
		printf("2.*************¼��ѧ����Ϣ*****************\n");
		printf("3.*************�޸�ѧ����Ϣ*****************\n");
		printf("4.*************ɾ��ѧ����Ϣ*****************\n");
		printf("5.*************��ӡ����ѧ����Ϣ*************\n");
		printf("6.*************ѧ����Ϣ����*****************\n");
		printf("7.*************�˳���Ϣ����ϵͳ*************\n");
		printf("��������Ӧ��ָ�\n");
		scanf("%d", &input);
		while ((getchar()) != '\n' ) {}
		if (input != 7 && input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6)
			printf("�����������������\n");
		else {
			return input;
			break;
		}
	}
}

/*
	���ܣ��鿴¼��ѧ����Ϣ
	������stu_info �ṹ������	count ѧ������
	����ֵ��
			-1		δ�ҵ�
			�±�	�ҵ�
*/
int get_stu_info(struct stu stu_info[], int id) {

	for (int i = 0; i < count; i++) {	//���ҽṹ�����Ƿ��д�ѧ��
		if (id == stu_info[i].id)
			return i;
	}
	return -1;
}

/*
	���ܣ�ͨ�������鿴¼��ѧ����Ϣ
	������stu_info �ṹ������	const char* pn	ѧ������
	����ֵ��mum
			
*/
int* get_stu_name_info(struct stu stu_info[], char* pn) {
 
	static int num[length] = { 0 };
	int n = 1;
	memset(num, 0, sizeof(num));
	for (int i = 0; i < count; i++) {	//���ҽṹ�����Ƿ��д�����
		if (strcmp(pn,stu_info[i].name) == 0) {
			num[n] = i;
			n++;
			num[0]++;
		}
			

	}
	return num;
}

/*
	���ܣ�¼��ѧ����Ϣ
	������stu_info[]ѧ���ṹ��	count ������
	����ֵ��
			-3		ȡ��¼��
			ѧ��	¼��ɹ�
*/
int input_stu_info(struct stu stu_info[]) {
	int id = 0;
	int mode = 0;
	//����id
	while (1) {
		printf("�봴��ѧ��id:\n");
		scanf("%d", &id);
		while ((getchar()) != '\n') {}
		if (-1 != get_stu_info(stu_info, id)) {	//�ж�id�Ƿ�Ϸ�
			printf("��ѧ���ѱ�ռ��\n");
			continue;
		}
		else if (id <= 0 || check_stu_id(id) != id_len) {
			printf("������ 1---%d ��Χ�ڵ�ѧ��\n", length - 1);
			continue;
		}
		else {
			stu_info[count].id = id;
			break;
		}
			
	}

	//��������
	while (1) {
		printf("������ѧ��������\n");
		printf("��������¼��\n");
		scanf("%s", stu_info[count].name);
		while ((getchar()) != '\n') {}
		if (isChineseString(stu_info[count].name) == 0) {
			printf("����������Ǵ����ģ�����������\n");
		}
		else if (isChineseString(stu_info[count].name) == 1) {
			break;
		}
	}

	//�����Ա�
	while (1) {							
		mode = 0;
		printf("��ѡ��ѧ���Ա�\n");
		printf("1.����\n");
		printf("2.Ů��\n");
		printf("3.�˳�\n");
		scanf("%d", &mode);
		while ((getchar()) != '\n') {}
		if (mode != 1 && mode != 2 && mode != 3) {
			printf("�Ƿ����룬������ѡ��\n");
		}
		else
			break;
	}
	switch (mode) {
	case 1: {
		strncpy(stu_info[count].sex, "��", 15);
		break;
	}
	case 2: {
		strcpy(stu_info[count].sex, "Ů");
		break;
	}
	case 3: {	//ɾ��
		stu_info[count] = stu_info[count + 1];//����
		return -3;
	}
	}
	//�������
	do {

		printf("������ѧ������:\n");
		scanf("%f", &stu_info[count].score);
		while ((getchar()) != '\n') {}
		if (stu_info[count].score <= 0 || stu_info[count].score > 1000) {
			printf("����������0-1000֮��!\n");
		}
		else {
			break;
		}
	} while (1);
	count++;	//ͳ��¼������
	return id;
}

/*
	���ܣ��޸�ѧ����Ϣ
	������stu_info[] ѧ���ṹ��		
	����ֵ��
*/
void change_stu_info(struct stu stu_info[]) {
	int id = 0;		//ѧ��
	char ch = 0;	//�ж��ַ�
	int input = 0;	//����޸���Ϣ��־
	struct stu n_stu = {0};	//���Ҫ�޸ĵ���Ϣ
	while (1) {
		printf("��������Ҫ�޸���Ϣ��ѧ��ѧ��:\n");	//����id���ж��Ƿ�Ϸ�
		scanf("%d", &id);
		while ((getchar()) != '\n' ) {}
		id = get_stu_info(stu_info, id);	//�����±긳ֵ��id
		if (id == -1) {
			printf("δ�ҵ���ѧ��\n");
			printf("�Ƿ�Ҫ���²��ң�y/n��");
			scanf("%c", &ch);
			while ((getchar()) != '\n' ) {}
			if (ch == 'y' || ch == 'Y')
				continue;
			else
				break;
		}
		my_printf(stu_info, id);
		do {	//�޸���Ϣ
			printf("��������Ҫ�޸ĵ���Ϣ��\n");
			printf("1.�޸�ѧ��\n");
			printf("2.�޸�����\n");
			printf("3.�޸��Ա�\n");
			printf("4.�޸ķ���\n");
			printf("0.�˳�\n");
			scanf("%d", &input);
			while ((getchar()) != '\n' ) {}
			switch (input) {
			case 1: {	//�޸�ѧ��
				printf("�������µ�ѧ�ţ�\n");
				scanf("%d", &n_stu.id);
				while ((getchar()) != '\n' ) {}
				if (n_stu.id <= 0) {
					printf("�µ�ѧ�ŷǷ�\n");
					break;
				}
				if (get_stu_info(stu_info, n_stu.id) == -1) {
					stu_info[id].id = n_stu.id;
					printf("�޸ĳɹ�\n");
					my_printf(stu_info, id);
					break;
				}
				else {
					printf("��ѧ���Ѿ���ʹ��\n");
					break;
				}

				}
			case 2: {	//�޸�����
				printf("�������µ�������\n");
				scanf("%s", stu_info[id].name);
				while ((getchar()) != '\n' ) {}
				printf("�����޸ĳɹ�\n");
				my_printf(stu_info, id);
				break;
			}
			case 3: {	//�޸��Ա�
				printf("�������µ��Ա�\n");
				scanf("%s", stu_info[id].sex);
				printf("�Ա��޸ĳɹ�\n");
				my_printf(stu_info, id);
				break;
			}
			case 4: {	//�޸ķ���
				printf("�������µķ���:\n");
				scanf("%f", &stu_info[id].score);
				printf("�����޸ĳɹ�\n");
				my_printf(stu_info, id);
				break;
			}
			}

		} while (input);
		printf("�Ƿ�����޸�ѧ����Ϣ��y/n����\n");
		scanf("%c", &ch);
		if (ch == 'y' || ch == 'Y')
			continue;
		else
			break;

	}


	


}

/*
	���ܣ�ɾ��ѧ����Ϣ
	������
	����ֵ��
*/
void delete(struct stu stu_info[]) {
	int n = 0;	//��ѯ��ʽ��ʶ
	char ch = 0;	//�˳���ʶ
	struct stu d_stu = { 0 };	//�����Ҫɾ����ѧ����Ϣ
	int* num = NULL;
	int j = 1;		//�����
	int m = 0;	//�ӷ���ֵ
	do {
		while (1) {
			printf("��������Ҫɾ����ѧ����Ϣ:\n");
			printf("1.��ѧ�Ų���\n");
			printf("2.����������\n");
			printf("0.�˳�\n");
			scanf("%d", &n);
			while ((getchar()) != '\n' ) {}
			if (n != 1 && n != 2 && n != 0) {
				printf("ָ���������������\n");
			}
			else {
				break;
			}
		}
		switch (n) {
		case 2: {	//����������
			printf("��������Ҫɾ��ѧ����������\n");
			scanf("%s", d_stu.name);
			while ((getchar()) != '\n') {}
			num = get_stu_name_info(stu_info, d_stu.name);	//��ȡ�����±�
			if (*num == 0) {							//����ѧ�Ŵ���
				printf("�������������ѧ��������\n");
				printf("�Ƿ��������루y/n����\n");
				scanf("%c", &ch);
				if (ch == 'y' || ch == 'Y')
					continue;
				else
					break;
			}
			else {			////����ѧ����ȷ
					j = 1;
					for (int i = 1; i <= *num; i++) {
						/*if (m != -1 && i < *num) {
							printf("%d.\t", j++);
						}*/
						m = my_printf(stu_info, *(num + i));	//��ӡ��ͬ������ѧ��

					}


			}


		}
		case 1: {	//��ѧ�Ų���
			while (1) {
				printf("��������Ҫɾ��ѧ����ѧ�ţ�\n");
				scanf("%d", &d_stu.id);
				while ((getchar()) != '\n' ) {}
				d_stu.id = get_stu_info(stu_info, d_stu.id);	//��ȡ�����±�
				if (d_stu.id == -1) {							//����ѧ�Ŵ���
					printf("����ѧ�Ŵ�����ѧ�Ų�����\n");
					printf("�Ƿ��������루y/n����\n");
					scanf("%c", &ch);
					if (ch == 'y' || ch == 'Y')
						continue;
					else										
						break;
				}
				else {			////����ѧ����ȷ
					id_delete(stu_info, d_stu);	//����ѧ��ɾ��ѧ��ɾ��
						printf("ɾ����ϣ��Ƿ����ɾ����y/n����");
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
	���ܣ���ѧ�Ż��������
	������struct stu stu_info[] ѧ����Ϣ����, int mode ����ģʽ
	����ֵ��
			1	ѧ������
			2	�ɼ�
			0	�������
*/
int sort_stu_info(struct stu stu_info[], int mode) {

	struct stu t_stu = { 0 };
	char ch = 0;	//�����û�����
	if (mode == 1) {

		printf("��ѧ���������У�\n");
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
		printf("���ɼ��������У�\n");
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
	���ܣ���ӡѧ����Ϣ
	������
	����ֵ��
				1		��ѧ�������ӡѧ����Ϣ
				2		���ɼ������ӡѧ����Ϣ
				3		�������δ�ӡ��ӡѧ����Ϣ
				4		���Ա��ӡ��Ϣ
*/
int* stu_print(struct stu stu_info[], int mode) {
	float beg_sco = 0;	//������ʼ������
	float end_sco = 0;	//�������������
	float sbeg_sco = 0;	//ѧ����ʼ������
	float send_sco = 0;	//ѧ������������
	float score[length] = { 0 };	//��ŷ��������Ľṹ�������±�
	//score[0]�������
	static int n[length] = { 0 };		//��ŷ��������Ľṹ�������±꣬n[0]�������
	int j = 1;			//�������ж�
	switch (mode) {
	case 1: {	//��ѧ�������ӡѧ����Ϣ
		memset(n, 0, sizeof(n));
		sort_stu_info(stu_info, 1);
		n[0] = count;
		return n;
		break;
	}
	case 2: {	//���ɼ������ӡѧ����Ϣ
		memset(n, 0, sizeof(n));
		sort_stu_info(stu_info, 2);
		n[0] = count;
		return n;
		break;
	}
	case 3: {	//�������δ�ӡ��ӡѧ����Ϣ
		//�������ѧ���ɼ�����
		sort_stu_info(stu_info, 2);
		sbeg_sco = stu_info[count - 1].score;
		send_sco = stu_info[0].score;
		//�������䲢�ж��Ƿ�Ϸ�
		while (1) {
			printf("ѧ���ĳɼ�����Ϊ��%f ---- %f\n", sbeg_sco, send_sco);
			printf("��������ʼ������\n");
			scanf("%f", &beg_sco);
			while ((getchar()) != '\n') {}
			printf("���������������\n");
			scanf("%f", &end_sco);
			while ((getchar()) != '\n') {}
			if (beg_sco < sbeg_sco || beg_sco > send_sco || end_sco < sbeg_sco || end_sco > send_sco || beg_sco > end_sco) {
				printf("�ɼ�����Ƿ�������������\n");
			}
			else
				break;
		}
		//����
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
	case 4: {	//���Ա��ӡ��Ϣ
		while (1) {
			printf("��������Ҫ��ӡ���Ա��ţ�\n");
			printf("1.��ӡ��������\n");
			printf("2.��ӡ����Ů��\n");
			printf("3.�˳�\n");
			scanf("%d", &j);
			while ((getchar()) != '\n') {}
			if (j != 1 && j != 2 && j != 3) {
				printf("�Ƿ����룬����������\n");
			}
			else
				break;
		}
		//����
		memset(n, 0, sizeof(n));
		if (j == 1) {
			for (int i = 0; i < count; i++) {
				if (strcmp(stu_info[i].sex, "��") == 0) {
					n[j] = i;
					n[0]++;
					j++;
				}
			}
		}
		else if (j == 2) {
			for (int i = 0; i < count; i++) {
				if (strcmp(stu_info[i].sex, "Ů") == 0) {
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
	���ܣ��ж��ַ����Ƿ�ȫΪ����
	������char* str	�ַ����׵�ַ
	����ֵ��
				0	�Ǵ�����
				1	������
*/
// �ж������ַ�
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

// �ж��ַ����Ƿ�ȫΪ����
int isChineseString(char* str) {
	//char* p = str;
	//while (*str != '\0') {
	//	short ch = *(short*)p; // ȡ�����ֽ�
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
	���ܣ�����ѧ��λ��
	������int id
	����ֵ
		dig		���ȷ�������ѧ��λ��
		id_len	��ȷ��ع涨λ��
*/
int check_stu_id(int id) {

	int dig = 0;

	// ����ѧ����λ��
	while (id > 0) {
		dig++;
		id /= 10;
	}

	// ��Ҫ�󳤶�У��
	if (dig < id_len) {
		return id_len;
	}
	else {
		return dig;
	}

}

/*
	���ܣ�����ѧ��ɾ��ѧ����Ϣ
	������struct stu stu_info[] ѧ����Ϣ�ṹ����, struct stu d_stu �����Ҫɾ����ѧ����Ϣ
	����ֵ����
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
		stu_info[d_stu.id] = stu_info[count - 1];	//���һ��ѧ������Ϣ������Ҫɾ����ѧ�����ﵽɾ��Ч��
		stu_info[count - 1].id = 0;
		memset(stu_info[count - 1].name, 0, sizeof(stu_info[count - 1].name));
		memset(stu_info[count - 1].sex, 0, sizeof(stu_info[count - 1].sex));
		stu_info[count - 1].score = 0;
		count--;
	}
}