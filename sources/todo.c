#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "todo.h"

/*할 일 입력받는 함수*/
void todo(Todo* ps) {
	int i;
	for (i = 0; i < 30; i++) {

		printf("할 일을 하나씩 입력하세요(end를 입력하면 종료): ");
		fgets(ps->tasks, sizeof(ps->tasks), stdin);
		ps->tasks[strlen(ps->tasks) - 1] = '\0';      //개행문자 제거
		if (strcmp(ps->tasks, "end") == 0) {      //end를 입력하면 할 일 입력 받기 중지
			break;
		}
		ps->str[i] = (char*)malloc(strlen(ps->tasks) + 1);  //할 일을 저장할 메모리 동적할당
		if (ps->str[i] == NULL) {                     //동적 할당에 실패할 경우
			printf("메모리가 부족합니다.\n");
			exit(1);                              // 프로그램 종료
		}
		strcpy_s(ps->str[i], strlen(ps->tasks) + 1, ps->tasks);     //할 일 동적 메모리에 복사
		ps->count++;   //할 일 수 세기

	}
}