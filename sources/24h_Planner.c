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
		scanf_s("%s", tasks, (int)sizeof(tasks));
		if (strcmp(tasks, "end") == 0) {
			break;
		}
		str[i] = (char*)calloc(100, strlen(tasks) + 1);
		if (str[i] == NULL) {
			printf("메모리가 부족합니다.\n");
			exit(1);
		}
		strcpy_s(str[i],sizeof(str[i]),tasks);
		count++;
		
	}
	
	for (i = 0; i < count; i++) {
		printf("%s\n", str[i]);
	}
	/*예상 소요시간과 난이도를 입력 받는 코드 블록*/
	
	for (i = 0; i < count; i++) {
		free(str[i]);
	}
	
	return 0;
}