#include "todo.h"
#include "time_calculate.h"
#include <stddef.h>
#include<stdlib.h>
#include <stdio.h>

/*예상 소요시간과 난이도의 차 구하는 함수*/

double Gap(double reqt, int level) {
	double gap = reqt - (double)level;
	return gap;
}

/*집중 모드*/
void calculate1(Todo* ps, Modeset* pset, Print_time* ptime) {
	int i;
	double req_time=-1;  //예상 소요시간 변수
	int level;       //난이도 변수
	double gap;

	for (i = 0; i < ps->count; i++) {
		printf("%s의 예상 소요시간을 입력하세요: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s의 난이도를 입력하세요(1~5): ", ps->str[i]);
		scanf_s("%d", &level);
		gap = Gap(req_time, level);

		/*예상 소요시간에 비해 난이도가 어려운 경우*/
		if (gap < -2) {
			req_time += 1;                //예상 소요시간에 +1 가중치 부여
		}
		else if (gap < -1) {
			req_time += 0.5;              //예상 소요시간에 +0.5 가중치 부여
		}
		else if (-1 <= gap && gap <= 1) {
			req_time += 0;               // 예상 소요시간 그대로 유지
		}
		/*예상 소요시간에 비해 난이도가 쉬운 경우*/
		else if (1 < gap && gap <= 2) {
			req_time -= 0.5;             //예상 소요시간에 -0.5 가중치 부여
		}
		else if (gap > 2) {
			req_time -= 1;               //예상 소요시간에 -1 가중치 부여
		}
		ptime->setting_time[i] = (double*)malloc(sizeof(double));  //할 일 시작하는 시간 저장하는 동적 메모리 할당
		if (ptime->setting_time[i] == NULL) {
			exit(1);
		}
		ptime->end[i] = (double*)malloc(sizeof(double));          //할 일 끝나는 시간 저장하는 동적 메모리 할당
		if (ptime->end[i] == NULL) {
			exit(1);
		}
		if (i == 0) {
			*(ptime->setting_time[i]) = pset->start;
		}
		else {
			*(ptime->setting_time[i]) = *(ptime->end[i - 1]);
		}
		*(ptime->end[i]) = *(ptime->setting_time[i]) + req_time;       //할 일이 끝나는 시간 = 다음 할 일 시작 시간
		
	}
	if (**ptime->end + ps->count-1 > 24) {
		printf("\n*할 일을 줄이고 여유시간을 확보해 보세요*\n");  //스케줄 시간이 하루(24시)를 넘어갈 시 삶의 밸런스를 위해 권고 메시지 출력
	}
}
/*여유모드*/
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime) {
	int i;
	double req_time=-1;  //예상 소요시간 변수
	int level;        //난이도 변수
	double gap;       //예상 소요시간 - 난이도

	for (i = 0; i < ps->count; i++) {

		printf("%s의 예상 소요시간을 입력하세요: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s의 난이도를 입력하세요(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = Gap(req_time, level);

		/*예상 소요시간에 비해 난이도가 어려운 경우*/
		if (gap <= -1) {
			req_time += 1;
		}
		else if (-1 < gap < 0) {
			req_time += 0;
		}
		/*예상 소요시간에 비해 난이도가 쉬운 경우*/
		else if (gap >= 1) {
			req_time += 0.5;      // 여유모드이므로 추가시간 있음
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
		printf("\n*할 일을 줄이고 여유시간을 확보해 보세요*\n");  //스케줄 시간이 하루(24시)를 넘어갈 시 삶의 밸런스를 위해 권고 메시지 출력
	}
}
