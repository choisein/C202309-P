#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time_calculate.h"   //������ �Է¹ް� �ð� �����ϴ� �Լ� �ҷ�����
#define MAX_TASKS 100


double Gap(double reqt, int level); // ���� �ҿ�ð��� ����ġ �ο��ϴ� �Լ� ����

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
			break;     //������ �ۼ� ����
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

