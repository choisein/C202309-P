#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "todo.h"

/*�� �� �Է¹޴� �Լ�*/
void todo(Todo* ps) {
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