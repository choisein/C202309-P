#include "todo.h"

typedef struct {
	int modenum;
	double start;
}Modeset;          //���� ���� �ð� ����ü ����

typedef struct {
	double* end[100];  //�� �� ������ �ð� ����
	double *setting_time[100];    //�� �� �����ϴ� �ð� ����
}Print_time;     //�����ٺ� �ð� ����ü ����

void calculate1(Todo* ps, Modeset* pset, Print_time* ptime);
void calculate2(Todo* ps, Modeset* pset, Print_time* ptime);


