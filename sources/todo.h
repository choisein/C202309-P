#ifndef _TODO_H_  //_TODO_H_ 매크로명이 정의되어 있지 않으면 
#define _TODO_H_  // _TODO_H_ 정의

#define MAX_TASKS 100

typedef struct {
	char tasks[MAX_TASKS];
	char* str[MAX_TASKS];
	int count;
}Todo;            //할 일 입력 받는 구조체 선언

/*할 일 입력받는 함수*/
void todo(Todo* ps);

#endif
