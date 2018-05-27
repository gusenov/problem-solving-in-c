#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define BUFFER_SIZE 256

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

typedef struct job vacancy;
struct job {
	char *name_of_company;  // наименование организации.
	char *position;  // должность.
	char *required_qualification;  // требуемая квалификация (образование, разряд).
	unsigned short int work_experience;  // стаж работы.
	float salary;  // заработная плата.
};

#define DATA_CNT 10
vacancy data[DATA_CNT] = {
	{ "АвтоклассЭкспресс", "водитель", "водительские права категории B", 5, 30000 },
	{ "КредитКапитал", "бухгалтер", "образование высшее профильное (желательно по специальности \"Бух. учёт, анализ и аудит\")", 10, 31000 },
	{ "АрбитрКонсалт", "администратор", "уверенный пользователь пакета офисных программ (Power Point, Excel, Word, Outlook)", 3, 29000 },
	{ "ЧистольонЛеда", "уборщик", "опыт работы в данной сфере", 1, 20500 },
	{ "МеридианЗолотой карат", "охранник", "знания инструкций по обеспечению безопасности сотрудников офиса при пожаре, аварии или в случае угроз режимных помещений", 2, 25000 },
	{ "СахарЛатте", "официант", "опыт работы на аналогичной должности - желателен", 1, 22000 },
	{ "МаксимумФлагман", "продавец-консультант", "опыт работы продавцом", 1, 23000 },
	{ "ЕвропаАэрохолл", "грузчик", "желателен опыт работы на складе", 0, 21000 },
	{ "ФармадарЗнахарь", "менеджер по продажам", "высшее образование", 4, 28000 },
	{ "АзбукаМетида", "курьер", "водительские права категории A", 0, 10000 }
};

// Процедура для вывода вакансии на экран:
void printjob(vacancy v) {
	printf("\n=== %s, %s ===\n", v.name_of_company, v.position);
	
	printf("Требования:\n");
	printf("\tопыт работы на аналогичной должности от %u лет;\n", v.work_experience);
	printf("\t%s.\n", v.required_qualification);

	printf("Условия:\n");
	printf("\tофициальная заработная плата – %.2f руб.\n", v.salary);
	
	printf("\n====================\n");
}

// Процедура поиска возможных рабочих мест:
void search(vacancy *jobs, int count, char *position, unsigned short int work_experience, float salary) {
	int i;
	for (i = 0; i < count; i++) {
		if (strcmp(jobs[i].position, position) == 0
			&& jobs[i].work_experience <= work_experience
			&& jobs[i].salary >= salary) {
			printjob(jobs[i]);
		}
	}
}

int main(int argc, char *argv[]) {
	char client_position[BUFFER_SIZE];  // должность клиента.
	unsigned short int client_work_experience;  // стаж работы клиента.
	float client_salary;  // заработная плата клиента.
	
	cyrillic();
	
	printf("Бюро занятости\n");
	printf("Введите сведения о своей квалификации и требованиях:\n");
	
	printf("Должность -> "); 
	fgets(client_position, BUFFER_SIZE, stdin);
	client_position[strcspn(client_position, "\n")] = '\0';
	
	printf("Стаж работы  -> "); 
	scanf("%hu", &client_work_experience);
	
	printf("Заработная плата -> "); 
	scanf("%f", &client_salary);
	
	printf("\n---------------------------------------------------------------------\n\n");
	
	search(data, DATA_CNT, client_position, client_work_experience, client_salary);

	system("pause");
	return 0;
}

