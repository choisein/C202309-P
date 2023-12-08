#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time_calculate.h"   //스케줄 입력받고 시간 조정하는 함수 불러오기
#define MAX_TASKS 100


double Gap(double reqt, int level); // 예상 소요시간에 가중치 부여하는 함수 정의

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
			break;     //스케줄 작성 종료
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

