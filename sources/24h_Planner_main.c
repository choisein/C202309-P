#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100

typedef struct {
	int modenum;
	double start;
}Modeset;          //모드와 시작 시간 구조체 선언

typedef struct {
	char tasks[100];
	char* str[100];
	int count;
}Todo;            //할 일 입력 받는 구조체 선언

typedef struct {
	double* end[100];  //할 일 끝나는 시각 변수
	double* setting_time[100];    //할 일 시작하는 시각 변수
}Print_time;     //스케줄 시간 구조체 선언

void todo(Todo* ps);
void calculate1(Todo* ps, Modeset* pset, Print_time* ptime);
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime);

int main(){
	while (1) {
		printf("24시간이 충분한 스케줄 플래너\n");
		printf("-----------------------------\n");

		/*모드 설정 코드 블록*/
		
		Modeset set = { 0, 0 };
		char mode[4][10] = { "직장", "공부", "휴일", "여행" };  //4가지 모드 배열에 저장
		printf("모드를 설정합니다.\n");
		printf("<집중 모드>\n");
		printf("1. 직장\n");
		printf("2. 공부\n");
		printf("<여유 모드>\n");
		printf("3. 휴일\n");
		printf("4. 여행\n");
		printf("------------------------------\n");
		printf("원하는 모드의 번호를 입력하세요: ");
		do {                                          //범위에 벗어난 모드 번호 입력시 경고 메시지 출력
			scanf_s("%d", &(set.modenum));
			if (set.modenum < 1 || set.modenum>4) {
				printf("1에서 4 사이의 번호를 입력하세요.");
			}
		} while (set.modenum < 1 || set.modenum>4);
		printf("%s모드", mode[set.modenum - 1]);
		printf("\n------------------------------\n");

		/*스케줄 시작 시간 설정 코드 블록*/

		printf("스케줄 시작 시간을 입력하세요(00시~24시): ");
		scanf_s("%lf", &(set.start));
		printf("%.1lf시", set.start);
		printf("\n------------------------------\n");

		getchar(); //버퍼에 남아있는 개행 문자 제거
		
		/*할 일 입력 받는 함수 호출*/

		Todo s1 = { "","",0 };
		todo(&s1);
		printf("------------------------------\n");

		/*예상 소요시간과 난이도를 입력 받는 함수 호출*/
		
		Print_time time;
		//집중모드
		if ((set.modenum == 1) || (set.modenum == 2)) {
			calculate1(&s1, &set, &time);

		}
		//여유모드
		if ((set.modenum == 3) || (set.modenum == 4)){
			calculate2(&s1, &set, &time);

		}	
		/*스케줄 플래너 출력*/

		printf("------------------------------\n");
		printf("플래너 작성 완료!\n");
		for (int i = 0; i < s1.count; i++) {
			printf("%.1f시-%.1f시: %s\n", *(time.setting_time[i]),*(time.end[i]), s1.str[i]);
		}
		
		/*스케줄 플래너 작성 후 메뉴 선택 코드 블록*/

		int menu_num;
		printf("\n------------------------------\n");
		printf("1. 플래너 추가하기 ");       //코드 반복
		printf("2. 종료하기 ");
		scanf_s("%d", &menu_num);
		if (menu_num == 2) {
			break;     //반복문 벗어나기
		}
		printf("\n");

		/*동적 메모리 반환*/
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
/*할 일 입력받는 함수*/
void todo(Todo *ps){
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
void calculate1(Todo* ps, Modeset *pset, Print_time *ptime) {
	int i;
	double req_time;  //예상 소요시간 변수
	int level;        //난이도 변수
	double gap;       //예상 소요시간 - 난이도
	
	for (i = 0; i < ps->count; i++) {
		printf("%s의 예상 소요시간을 입력하세요: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s의 난이도를 입력하세요(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = req_time - (double)level;    //예상 소요시간과 난이도의 차 구하기

		/*예상 소요시간에 비해 난이도가 어려운 경우*/

		if (gap < -2) {
			req_time += 1;                //예상 소요시간 +1
		}
		else if (gap < -1) {
			req_time += 0.5;              //예상 소요시간 +0.5
		}
		else if (-1 <= gap && gap <= 1) {
			req_time += 0;               // 예상 소요시간 그대로 유지
		}
		/*예상 소요시간에 비해 난이도가 쉬운 경우*/
		else if (1 < gap && gap <= 2) {
			req_time -= 0.5;             //예상 소요시간 -0.5
		}
		else if (gap > 2) {
			req_time -= 1;               //예상 소요시간 -1
		}
		ptime-> setting_time[i] = (double*)malloc(sizeof(double));  //할 일 시작하는 시간 저장하는 동적 메모리 할당
		if (ptime-> setting_time[i] == NULL) {
			exit(1);
		}
		ptime->end[i] = (double*)malloc(sizeof(double));          //할 일 끝나는 시간 저장하는 동적 메모리 할당
		if (ptime->end[i] == NULL) {
			exit(1);
		}
		if (i == 0) {
			*(ptime-> setting_time[i]) = pset->start;
		}
		else {
			*(ptime->setting_time[i]) = *(ptime-> end[i - 1]);
		}
		*(ptime-> end[i]) = *(ptime->setting_time[i]) + req_time;       //할 일이 끝나는 시간 = 다음 할 일 시작 시간
	}
}

void calculate2(Todo* ps, Modeset *pset, Print_time *ptime) {
	int i;
	double req_time;  //예상 소요시간 변수
	int level;        //난이도 변수
	double gap;       //예상 소요시간 - 난이도

	for (i = 0; i < ps->count; i++) {

		printf("%s의 예상 소요시간을 입력하세요: ", ps->str[i]);
		scanf_s("%lf", &req_time);

		printf("%s의 난이도를 입력하세요(1~5): ", ps->str[i]);
		scanf_s("%d", &level);

		gap = req_time - (double)level;
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
}

