#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("24�ð��� ����� ������ �÷���\n");
	printf("-----------------------------\n");

	/*��� ���� �ڵ� ���*/
	int modenum;
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
	scanf_s("%d", &modenum);
	printf("%s���", mode[modenum - 1]);
	printf("\n------------------------------\n");

	/*������ ���� �ð� ���� �ڵ� ���*/
	double start;
	printf("������ ���� �ð��� �Է��ϼ���(00��~24��): ");
	scanf_s("%lf", &start);
	printf("%.1lf��", start);
	printf("\n------------------------------\n");

	/*�� �� �Է� �޴� �ڵ� ���*/
	char tasks[100] = { 0, };
	char* str[100];
	int i;
	int count = 0;
	

	for (i = 0; i < 30; i++) {
		
		printf("�� ���� �ϳ��� �Է��ϼ���(end�� �Է��ϸ� ����): ");
		scanf_s("%s", tasks, (unsigned int)sizeof(tasks));
		if (strcmp(tasks, "end") == 0) {      //end�� �Է��ϸ� �� �� �Է� �ޱ� ����
			break;
		}
		str[i] = (char*)malloc(strlen(tasks)+1);  //�� ���� ������ �޸� �����Ҵ�
		if (str[i] == NULL) {                     //�޸� �Ҵ翡 ������ ���
			printf("�޸𸮰� �����մϴ�.\n");
			exit(1);
		}
		strcpy_s(str[i],strlen(tasks)+1, tasks);     //�� �� ���� �޸𸮿� �迭�� ����
		count++;   //�� �� �� ����
		
	}
	
	/*���� �ҿ�ð��� ���̵��� �Է� �޴� �ڵ� ���*/
	double req_time;
	int level;
	double gap;
	double* end[10];
	double* setting_time[10];
	printf("------------------------------\n");
	//���߸��
	if ((modenum == 1) || (modenum == 2)) {
		for (i = 0; i < count; i++) {
			
			printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", str[i]);
			scanf_s("%lf", &req_time);
			
			printf("%s�� ���̵��� �Է��ϼ���(1~5): ", str[i]);
			scanf_s("%d", &level);
			
			gap = req_time - (double)level;    //���� �ҿ�ð��� ���̵��� �� ���ϱ�

			/*���� �ҿ�ð��� ���� ���̵��� ����� ���*/
			
			if (gap < -2) {                   
				req_time += 1;                //���� �ҿ�ð� +1
			}
			else if (gap < -1) {
				req_time += 0.5;              //���� �ҿ�ð� +0.5
			}
			else if (-1 <= gap <= 1) {
				req_time += 0;               // ���� �ҿ�ð� �״�� ����
			}
			/*���� �ҿ�ð��� ���� ���̵��� ���� ���*/
			else if (1 < gap <= 2) {         
				req_time -= 0.5;             //���� �ҿ�ð� -0.5
			}
			else if (gap > 2) {
				req_time -= 1;               //���� �ҿ�ð� -1
			}
			setting_time[i] = (double*)malloc(sizeof(double));
			if (setting_time[i] == NULL) {
				exit(1);
			}
			end[i] = (double*)malloc( sizeof(double));
			if (end[i] == NULL) {
				exit(1);
			}
			if (i == 0) {
				*setting_time[i] = start;
			}
			else {
				*setting_time[i] = *end[i - 1];
			}
			*end[i] = *setting_time[i] + req_time;       //�� ���� ������ �ð� = ���� �� �� ���� �ð�
		}
		printf("------------------------------\n");
		printf("�÷��� �ۼ� �Ϸ�!\n");
		for (i = 0; i < count; i++) {
			printf("%.1f��-%.1f��: %s\n", *setting_time[i], *end[i], str[i]);
		}
	}
	//�������
	if ((modenum == 3) || (modenum == 4)) {
		for (i = 0; i < count; i++) {

			printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", str[i]);
			scanf_s("%lf", &req_time);

			printf("%s�� ���̵��� �Է��ϼ���(1~5): ", str[i]);
			scanf_s("%d", &level);

			gap = req_time - (double)level;
			/*���� �ҿ�ð��� ���� ���̵��� ����� ���*/
			if (gap <= -1) {
				req_time += 1;
			}
			else if (-1< gap <0) {
				req_time += 0;
			}
			/*���� �ҿ�ð��� ���� ���̵��� ���� ���*/
			else if (gap >= 1) {
				req_time += 0.5;      // ��������̹Ƿ� �߰��ð� ����
			}
			setting_time[i] = (double*)malloc(sizeof(double));
			if (setting_time[i] == NULL) {
				exit(1);
			}
			end[i] = (double*)malloc(sizeof(double));
			if (end[i] == NULL) {
				exit(1);
			}
			if (i == 0) {
				*setting_time[i] = start;
			}
			else {
				*setting_time[i] = *end[i - 1];
			}
			*end[i] = *setting_time[i] + req_time;
		}
		printf("------------------------------\n");
		printf("�÷��� �ۼ� �Ϸ�!\n");
		for (i = 0; i < count; i++) {
			printf("%.1f��-%.1f��: %s\n", *setting_time[i], *end[i], str[i]);
		}
	}
	/*���� �޸� ��ȯ*/
	for (i = 0; i < count; i++) {
		free(str[i]);
	}
	for (i = 0; i < count; i++) {
		free(setting_time[i]);
	}
	for (i = 0; i < count; i++) {
		free(end[i]);
	}
	
	return 0;
}