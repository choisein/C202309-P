#include "todo.h"
#include "time_calculate.h"
#include <stddef.h>
#include<stdlib.h>
#include <stdio.h>

/*���� �ҿ�ð��� ���̵��� �� ���ϴ� �Լ�*/

double Gap(double reqt, int level) {
	double gap = reqt - (double)level;
	return gap;
}

/*���� ���*/
void calculate1(Todo* ps, Modeset* pset, Print_time* ptime) {
	int i;
	double req_time=-1;  //���� �ҿ�ð� ����
	int level;       //���̵� ����
	double gap;

	for (i = 0; i < ps->count; i++) {
		printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s�� ���̵��� �Է��ϼ���(1~5): ", ps->str[i]);
		scanf_s("%d", &level);
		gap = Gap(req_time, level);

		/*���� �ҿ�ð��� ���� ���̵��� ����� ���*/
		if (gap < -2) {
			req_time += 1;                //���� �ҿ�ð��� +1 ����ġ �ο�
		}
		else if (gap < -1) {
			req_time += 0.5;              //���� �ҿ�ð��� +0.5 ����ġ �ο�
		}
		else if (-1 <= gap && gap <= 1) {
			req_time += 0;               // ���� �ҿ�ð� �״�� ����
		}
		/*���� �ҿ�ð��� ���� ���̵��� ���� ���*/
		else if (1 < gap && gap <= 2) {
			req_time -= 0.5;             //���� �ҿ�ð��� -0.5 ����ġ �ο�
		}
		else if (gap > 2) {
			req_time -= 1;               //���� �ҿ�ð��� -1 ����ġ �ο�
		}
		ptime->setting_time[i] = (double*)malloc(sizeof(double));  //�� �� �����ϴ� �ð� �����ϴ� ���� �޸� �Ҵ�
		if (ptime->setting_time[i] == NULL) {
			exit(1);
		}
		ptime->end[i] = (double*)malloc(sizeof(double));          //�� �� ������ �ð� �����ϴ� ���� �޸� �Ҵ�
		if (ptime->end[i] == NULL) {
			exit(1);
		}
		if (i == 0) {
			*(ptime->setting_time[i]) = pset->start;
		}
		else {
			*(ptime->setting_time[i]) = *(ptime->end[i - 1]);
		}
		*(ptime->end[i]) = *(ptime->setting_time[i]) + req_time;       //�� ���� ������ �ð� = ���� �� �� ���� �ð�
		
	}
	if (**ptime->end + ps->count-1 > 24) {
		printf("\n*�� ���� ���̰� �����ð��� Ȯ���� ������*\n");  //������ �ð��� �Ϸ�(24��)�� �Ѿ �� ���� �뷱���� ���� �ǰ� �޽��� ���
	}
}
/*�������*/
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime) {
	int i;
	double req_time=-1;  //���� �ҿ�ð� ����
	int level;        //���̵� ����
	double gap;       //���� �ҿ�ð� - ���̵�

	for (i = 0; i < ps->count; i++) {

		printf("%s�� ���� �ҿ�ð��� �Է��ϼ���: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s�� ���̵��� �Է��ϼ���(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = Gap(req_time, level);

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
	if (**ptime->end + ps->count - 1 > 24) {
		printf("\n*�� ���� ���̰� �����ð��� Ȯ���� ������*\n");  //������ �ð��� �Ϸ�(24��)�� �Ѿ �� ���� �뷱���� ���� �ǰ� �޽��� ���
	}
}
