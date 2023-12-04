#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100

typedef struct {
	int modenum;
	double start;
}Modeset;          //���� ���� �ð� ����ü ����

typedef struct {
	char tasks[100];
	char* str[100];
	int count;
}Todo;            //�� �� �Է� �޴� ����ü ����

typedef struct {
	double* end[100];  //�� �� ������ �ð� ����
	double* setting_time[100];    //�� �� �����ϴ� �ð� ����
}Print_time;     //������ �ð� ����ü ����

void todo(Todo* ps);
void calculate1(Todo* ps, Modeset* pset, Print_time* ptime);
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime);

int main(){
	while (1) {
		printf("24�ð��� ����� ������ �÷���\n");
		printf("-----------------------------\n");

		/*��� ���� �ڵ� ���*/
		
		Modeset set = { 0, 0 };
		char mode[4][10] = { "����", "����", "����", "����" };  //4���� ��� �迭�� ����
		printf("��带 �����մϴ�.\n");
		printf("<���� ���>\n");
		printf("1. ����\n");
		printf("2. ����\n");
		printf("<���� ���>\n");
		printf("3. ����\n");
		printf("4. ����\n");
		printf("------------------------------\n");
		printf("���ϴ� ����� ��ȣ�� �Է��ϼ���: ");
		do {                                          //������ ��� ��� ��ȣ �Է½� ��� �޽��� ���
			scanf_s("%d", &(set.modenum));
			if (set.modenum < 1 || set.modenum>4) {
				printf("1���� 4 ������ ��ȣ�� �Է��ϼ���.");
			}
		} while (set.modenum < 1 || set.modenum>4);
		printf("%s���", mode[set.modenum - 1]);
		printf("\n------------------------------\n");

		/*������ ���� �ð� ���� �ڵ� ���*/

		printf("������ ���� �ð��� �Է��ϼ���(00��~24��): ");
		scanf_s("%lf", &(set.start));
		printf("%.1lf��", set.start);
		printf("\n------------------------------\n");

		getchar(); //���ۿ� �����ִ� ���� ���� ����
		
		/*�� �� �Է� �޴� �Լ� ȣ��*/

		Todo s1 = { "","",0 };
		todo(&s1);
		printf("------------------------------\n");

		/*���� �ҿ�ð��� ���̵��� �Է� �޴� �Լ� ȣ��*/
		
		Print_time time;
		//���߸��
		if ((set.modenum == 1) || (set.modenum == 2)) {
			calculate1(&s1, &set, &time);

		}
		//�������
		if ((set.modenum == 3) || (set.modenum == 4)){
			calculate2(&s1, &set, &time);

		}	
		/*������ �÷��� ���*/

		printf("------------------------------\n");
		printf("�÷��� �ۼ� �Ϸ�!\n");
		for (int i = 0; i < s1.count; i++) {
			printf("%.1f��-%.1f��: %s\n", *(time.setting_time[i]),*(time.end[i]), s1.str[i]);
		}
		
		/*������ �÷��� �ۼ� �� �޴� ���� �ڵ� ���*/

		int menu_num;
		printf("\n------------------------------\n");
		printf("1. �÷��� �߰��ϱ� ");       //�ڵ� �ݺ�
		printf("2. �����ϱ� ");
		scanf_s("%d", &menu_num);
		if (menu_num == 2) {
			break;     //�ݺ��� �����
		}
		printf("\n");

		/*���� �޸� ��ȯ*/
		int i;
		for (i = 0; i < s1.count; i++) {
			free(s1.str[i]);
		}
		for (i = 0; i < s1.count; i++) {
			free(time.setting_time[i]);
		}
		for (i = 0; i < s1.count; i++) {
			free(time.end[i]);
		}
	}
	return 0;
}
/*�� �� �Է¹޴� �Լ�*/
void todo(Todo *ps){
	int i;
	for (i = 0; i < 30; i++) {

		printf("�� ���� �ϳ��� �Է��ϼ���(end�� �Է��ϸ� ����): ");
		fgets(ps->tasks, sizeof(ps->tasks), stdin);
		ps->tasks[strlen(ps->tasks) - 1] = '\0';      //���๮�� ����
		if (strcmp(ps->tasks, "end") == 0) {      //end�� �Է��ϸ� �� �� �Է� �ޱ� ����
			break;
		}
		ps->str[i] = (char*)malloc(strlen(ps->tasks) + 1);  //�� ���� ������ �޸� �����Ҵ�
		if (ps->str[i] == NULL) {                     //���� �Ҵ翡 ������ ���
			printf("�޸𸮰� �����մϴ�.\n");
			exit(1);                              // ���α׷� ����
		}
		strcpy_s(ps->str[i], strlen(ps->tasks) + 1, ps->tasks);     //�� �� ���� �޸𸮿� ����
		ps->count++;   //�� �� �� ����

	}
}
void calculate1(Todo* ps, Modeset *pset, Print_time *ptime) {
	int i;
	double req_time;  //���� �ҿ�ð� ����
	int level;        //���̵� ����
	double gap;       //���� �ҿ�ð� - ���̵�
	
	for (i = 0; i < ps->count; i++) {
		printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s�� ���̵��� �Է��ϼ���(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = req_time - (double)level;    //���� �ҿ�ð��� ���̵��� �� ���ϱ�

		/*���� �ҿ�ð��� ���� ���̵��� ����� ���*/

		if (gap < -2) {
			req_time += 1;                //���� �ҿ�ð� +1
		}
		else if (gap < -1) {
			req_time += 0.5;              //���� �ҿ�ð� +0.5
		}
		else if (-1 <= gap && gap <= 1) {
			req_time += 0;               // ���� �ҿ�ð� �״�� ����
		}
		/*���� �ҿ�ð��� ���� ���̵��� ���� ���*/
		else if (1 < gap && gap <= 2) {
			req_time -= 0.5;             //���� �ҿ�ð� -0.5
		}
		else if (gap > 2) {
			req_time -= 1;               //���� �ҿ�ð� -1
		}
		ptime-> setting_time[i] = (double*)malloc(sizeof(double));  //�� �� �����ϴ� �ð� �����ϴ� ���� �޸� �Ҵ�
		if (ptime-> setting_time[i] == NULL) {
			exit(1);
		}
		ptime->end[i] = (double*)malloc(sizeof(double));          //�� �� ������ �ð� �����ϴ� ���� �޸� �Ҵ�
		if (ptime->end[i] == NULL) {
			exit(1);
		}
		if (i == 0) {
			*(ptime-> setting_time[i]) = pset->start;
		}
		else {
			*(ptime->setting_time[i]) = *(ptime-> end[i - 1]);
		}
		*(ptime-> end[i]) = *(ptime->setting_time[i]) + req_time;       //�� ���� ������ �ð� = ���� �� �� ���� �ð�
	}
}

void calculate2(Todo* ps, Modeset *pset, Print_time *ptime) {
	int i;
	double req_time;  //���� �ҿ�ð� ����
	int level;        //���̵� ����
	double gap;       //���� �ҿ�ð� - ���̵�

	for (i = 0; i < ps->count; i++) {

		printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s�� ���̵��� �Է��ϼ���(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = req_time - (double)level;
		/*���� �ҿ�ð��� ���� ���̵��� ����� ���*/
		if (gap <= -1) {
			req_time += 1;
		}
		else if (-1 < gap < 0) {
			req_time += 0;
		}
		/*���� �ҿ�ð��� ���� ���̵��� ���� ���*/
		else if (gap >= 1) {
			req_time += 0.5;      // ��������̹Ƿ� �߰��ð� ����
		}
		ptime->setting_time[i] = (double*)malloc(sizeof(double));
		if (ptime->setting_time[i] == NULL) {
			exit(1);
		}
		ptime->end[i] = (double*)malloc(sizeof(double));
		if (ptime->end[i] == NULL) {
			exit(1);
		}
		if (i == 0) {
			*(ptime->setting_time[i]) = pset->start;  
		}
		else {
			*(ptime->setting_time[i]) = *(ptime->end[i - 1]);
		}
		*(ptime->end[i]) = *(ptime->setting_time[i]) + req_time;
	}
}

