
#ifndef _TODO_H_  // todo.h 헤더파일 중복 방지
#define _TODO_H_  

#define MAX_TASKS 100

typedef struct {
	char tasks[MAX_TASKS];
	char* str[MAX_TASKS];
	int count;
}Todo;            //할 일 입력 받는 구조체 선언

/*할 일 입력받는 함수*/

void todo(Todo* ps);

#endif
