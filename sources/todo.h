
#ifndef _TODO_H_  // todo.h ������� �ߺ� ����
#define _TODO_H_  

#define MAX_TASKS 100

typedef struct {
	char tasks[MAX_TASKS];
	char* str[MAX_TASKS];
	int count;
}Todo;            //�� �� �Է� �޴� ����ü ����

/*�� �� �Է¹޴� �Լ�*/

void todo(Todo* ps);

#endif
