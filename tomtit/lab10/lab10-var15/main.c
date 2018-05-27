#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// ������� �� ���������:
void cyrillic() {
	// ��� ������ ����� ��� ����������� ����������� ���������:
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	// ����� ���� �������� ����� � ������� �� Lucida Console.
	// ��� ������ ������ �������� ������ ������� �� ������� ���������� ������ ���� �������. 
	// � ����������� ���� ��������� ���������. 
	// � ����������� ���� ��������� ������� ������ � ��� ��������� �Lucida Console�. 
}

typedef enum week weekday;
enum week { monday = 1, tuesday = 2, wednesday = 3, thursday = 4, friday = 5, saturday = 6, sunday = 7 };

struct tm {
	unsigned short int hh;
	unsigned short int mm;
};

struct duration {
	struct tm begin;
	struct tm end;
};

typedef struct lecture lesson;
struct lecture {
	weekday day;  // ���� ������. 
	struct duration time;  // ����� ����.
	unsigned short int classroom;  // ���������.
	char *subject;  // �������� ��������.
};

#define DATA_CNT 7
lesson data[DATA_CNT] = {
	{    monday, { {  8, 30 }, {  9, 15 } }, 1, "����������"      },
	{    monday, { { 17, 25 }, { 18, 10 } }, 1, "�����"           },
	{   tuesday, { { 10, 15 }, { 11,  0 } }, 2, "��������"        },
	{   tuesday, { { 19, 10 }, { 19, 55 } }, 2, "���������� ����" },
	{ wednesday, { { 12, 10 }, { 12, 55 } }, 3, "�����"           },
	{  thursday, { { 13, 55 }, { 14, 40 } }, 1, "������"          },
	{    friday, { { 15, 40 }, { 16, 25 } }, 1, "�����������"     }
};

// ��������� ������ �������� �������, ����� �������� ��������� ��������:
void search(lesson *lessons, int cnt, unsigned short int classroom) {
	int d, h, m;
	int i;
	bool busy = false;
	bool changed;
	
	printf("������� �������, ����� �������� ��������� ��������:\n");
	
	for (d = monday; d <= sunday; d++) {
		
		changed = true;
		
		switch(d) {
			case monday:    printf("�����������:\n"); break;
			case tuesday:   printf("�������:\n"); break;
			case wednesday: printf("�����:\n"); break;
			case thursday:  printf("�������:\n"); break;
			case friday:    printf("�������:\n"); break;
			case saturday:  printf("�������:\n"); break;
			case sunday:    printf("�����������:\n"); break;
			default: break;
		}
		
		for (h = 0; h < 24; h++) {
			for (m = 0; m < 60; m++) {
				
				for (i = 0; i < cnt; i++) {
					if (lessons[i].classroom == classroom) {
						if (busy) {
							if (lessons[i].day == d && lessons[i].time.end.hh == h  && lessons[i].time.end.mm == m) {
								busy = false;
								changed = true;
								break;
							}
						} else {
							if (lessons[i].day == d && lessons[i].time.begin.hh == h  && lessons[i].time.begin.mm == m) {
								busy = true;
								changed = true;
								break;
							}
						}
					}
				}
				
				if (changed) {
					if (!busy) {
						printf("\t%02d:%02d - ", h, m);
					} else {
						printf(" %02d:%02d\n", h, m);
					}
					changed = false;
				}
				
				if (!busy && h == 23 && m == 59) {
					printf(" %02d:%02d\n", h, m);
				}
				
			}
		}
	}
}

int main(int argc, char *argv[]) {
	unsigned short int classroom;
	
	cyrillic();
	
	printf("���� ��������� ���������\n");
	
	printf("��������� -> "); 
	scanf("%hu", &classroom);
	
	search(data, DATA_CNT, classroom);
	
	system("pause");
	return 0;
}

