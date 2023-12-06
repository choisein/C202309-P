
typedef struct {
	char tasks[100];
	char* str[100];
	int count;
}Todo;            //할 일 입력 받는 구조체 선언

/*할 일 입력받는 함수*/
void todo(Todo* ps);

