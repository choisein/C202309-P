#include <stdio.h>

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

	return 0;
}