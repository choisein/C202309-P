#include <stdio.h>

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
	char tasks[100][100];
	char ch;
	int i= 0;
	while (1) {
		printf("�� ���� �Է��ϼ���: ");
		scanf_s("%s", tasks[i], (int)sizeof(tasks[i]));
		ch = getchar();
		i++;
	}



	return 0;
}