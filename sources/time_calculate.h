#include "todo.h"

typedef struct {
	int modenum;
	double start;
}Modeset;          //모드와 시작 시간 구조체 선언

typedef struct {
	double* end[100];  //할 일 끝나는 시각 변수
	double *setting_time[100];    //할 일 시작하는 시각 변수
}Print_time;     //스케줄별 시간 구조체 선언

void calculate1(Todo* ps, Modeset* pset, Print_time* ptime);
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime);


