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
		scanf_s("%s", tasks, (int)sizeof(tasks));
		if (strcmp(tasks, "end") == 0) {
			break;
		}
		str[i] = (char*)calloc(100, strlen(tasks) + 1);
		if (str[i] == NULL) {
			printf("�޸𸮰� �����մϴ�.\n");
			exit(1);
		}
		strcpy_s(str[i],sizeof(str[i]),tasks);
		count++;
		
	}
	
	for (i = 0; i < count; i++) {
		printf("%s\n", str[i]);
	}
	/*���� �ҿ�ð��� ���̵��� �Է� �޴� �ڵ� ���*/
	
	for (i = 0; i < count; i++) {
		free(str[i]);
	}
	
	return 0;
}