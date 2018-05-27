#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// Переход на кириллицу:
void cyrillic() {
	// Эти строки нужны для правильного отображения кириллицы:
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	// Также надо изменить шрифт в консоли на Lucida Console.
	// Для замены шрифта кликаете правой кнопкой на надписи «Командная строка» окна консоли. 
	// В открывшемся меню выбираете «Свойства». 
	// В появившемся окне выбираете вкладку «Шрифт» и там выбираете «Lucida Console». 
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
	weekday day;  // день недели. 
	struct duration time;  // время пары.
	unsigned short int classroom;  // аудитория.
	char *subject;  // название предмета.
};

#define DATA_CNT 7
lesson data[DATA_CNT] = {
	{    monday, { {  8, 30 }, {  9, 15 } }, 1, "Математика"      },
	{    monday, { { 17, 25 }, { 18, 10 } }, 1, "Химия"           },
	{   tuesday, { { 10, 15 }, { 11,  0 } }, 2, "Биология"        },
	{   tuesday, { { 19, 10 }, { 19, 55 } }, 2, "Английский язык" },
	{ wednesday, { { 12, 10 }, { 12, 55 } }, 3, "Химия"           },
	{  thursday, { { 13, 55 }, { 14, 40 } }, 1, "Физика"          },
	{    friday, { { 15, 40 }, { 16, 25 } }, 1, "Информатика"     }
};

// Процедура поиска периодов времени, когда заданная аудитория свободна:
void search(lesson *lessons, int cnt, unsigned short int classroom) {
	int d, h, m;
	int i;
	bool busy = false;
	bool changed;
	
	printf("Периоды времени, когда заданная аудитория свободна:\n");
	
	for (d = monday; d <= sunday; d++) {
		
		changed = true;
		
		switch(d) {
			case monday:    printf("понедельник:\n"); break;
			case tuesday:   printf("вторник:\n"); break;
			case wednesday: printf("среда:\n"); break;
			case thursday:  printf("четверг:\n"); break;
			case friday:    printf("пятница:\n"); break;
			case saturday:  printf("суббота:\n"); break;
			case sunday:    printf("воскресенье:\n"); break;
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
	
	printf("Учет занятости аудитории\n");
	
	printf("Аудитория -> "); 
	scanf("%hu", &classroom);
	
	search(data, DATA_CNT, classroom);
	
	system("pause");
	return 0;
}

