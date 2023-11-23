#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	printf("24시간이 충분한 스케줄 플래너\n");
	printf("-----------------------------\n");

	/*모드 설정 코드 블록*/
	int modenum;
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
	scanf_s("%d", &modenum);
	printf("%s모드", mode[modenum - 1]);
	printf("\n------------------------------\n");

	/*스케줄 시작 시간 설정 코드 블록*/
	double start;
	printf("스케줄 시작 시간을 입력하세요(00시~24시): ");
	scanf_s("%lf", &start);
	printf("%.1lf시", start);
	printf("\n------------------------------\n");

	/*할 일 입력 받는 코드 블록*/
	char tasks[100] = { 0, };
	char* str[100];
	int i;
	int count = 0;
	

	for (i = 0; i < 30; i++) {
		
		printf("할 일을 하나씩 입력하세요(end를 입력하면 종료): ");
		scanf_s("%s", tasks, (unsigned int)sizeof(tasks));
		if (strcmp(tasks, "end") == 0) {      //end를 입력하면 할 일 입력 받기 중지
			break;
		}
		str[i] = (char*)malloc(strlen(tasks)+1);  //할 일을 저장할 메모리 동적할당
		if (str[i] == NULL) {                     //메모리 할당에 실패한 경우
			printf("메모리가 부족합니다.\n");
			exit(1);
		}
		strcpy_s(str[i],strlen(tasks)+1, tasks);     //할 일 동적 메모리에 배열로 저장
		count++;   //할 일 수 세기
		
	}
	
	/*예상 소요시간과 난이도를 입력 받는 코드 블록*/
	double req_time;
	int level;
	double gap;
	double* end[10];
	double* setting_time[10];
	printf("------------------------------\n");
	//집중모드
	if ((modenum == 1) || (modenum == 2)) {
		for (i = 0; i < count; i++) {
			
			printf("%s의 예상 소요시간을 입력하세요: ", str[i]);
			scanf_s("%lf", &req_time);
			
			printf("%s의 난이도를 입력하세요(1~5): ", str[i]);
			scanf_s("%d", &level);
			
			gap = req_time - (double)level;    //예상 소요시간과 난이도의 차 구하기

			/*예상 소요시간에 비해 난이도가 어려운 경우*/
			
			if (gap < -2) {                   
				req_time += 1;                //예상 소요시간 +1
			}
			else if (gap < -1) {
				req_time += 0.5;              //예상 소요시간 +0.5
			}
			else if (-1 <= gap <= 1) {
				req_time += 0;               // 예상 소요시간 그대로 유지
			}
			/*예상 소요시간에 비해 난이도가 쉬운 경우*/
			else if (1 < gap <= 2) {         
				req_time -= 0.5;             //예상 소요시간 -0.5
			}
			else if (gap > 2) {
				req_time -= 1;               //예상 소요시간 -1
			}
			setting_time[i] = (double*)malloc(sizeof(double));
			if (setting_time[i] == NULL) {
				exit(1);
			}
			end[i] = (double*)malloc( sizeof(double));
			if (end[i] == NULL) {
				exit(1);
			}
			if (i == 0) {
				*setting_time[i] = start;
			}
			else {
				*setting_time[i] = *end[i - 1];
			}
			*end[i] = *setting_time[i] + req_time;       //할 일이 끝나는 시간 = 다음 할 일 시작 시간
		}
		printf("------------------------------\n");
		printf("플래너 작성 완료!\n");
		for (i = 0; i < count; i++) {
			printf("%.1f시-%.1f시: %s\n", *setting_time[i], *end[i], str[i]);
		}
	}
	//여유모드
	if ((modenum == 3) || (modenum == 4)) {
		for (i = 0; i < count; i++) {

			printf("%s의 예상 소요시간을 입력하세요: ", str[i]);
			scanf_s("%lf", &req_time);

			printf("%s의 난이도를 입력하세요(1~5): ", str[i]);
			scanf_s("%d", &level);

			gap = req_time - (double)level;
			/*예상 소요시간에 비해 난이도가 어려운 경우*/
			if (gap <= -1) {
				req_time += 1;
			}
			else if (-1< gap <0) {
				req_time += 0;
			}
			/*예상 소요시간에 비해 난이도가 쉬운 경우*/
			else if (gap >= 1) {
				req_time += 0.5;      // 여유모드이므로 추가시간 있음
			}
			setting_time[i] = (double*)malloc(sizeof(double));
			if (setting_time[i] == NULL) {
				exit(1);
			}
			end[i] = (double*)malloc(sizeof(double));
			if (end[i] == NULL) {
				exit(1);
			}
			if (i == 0) {
				*setting_time[i] = start;
			}
			else {
				*setting_time[i] = *end[i - 1];
			}
			*end[i] = *setting_time[i] + req_time;
		}
		printf("------------------------------\n");
		printf("플래너 작성 완료!\n");
		for (i = 0; i < count; i++) {
			printf("%.1f시-%.1f시: %s\n", *setting_time[i], *end[i], str[i]);
		}
	}
	/*동적 메모리 반환*/
	for (i = 0; i < count; i++) {
		free(str[i]);
	}
	for (i = 0; i < count; i++) {
		free(setting_time[i]);
	}
	for (i = 0; i < count; i++) {
		free(end[i]);
	}
	
	return 0;
}