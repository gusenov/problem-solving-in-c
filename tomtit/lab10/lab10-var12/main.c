#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define BUFFER_SIZE 256

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

typedef struct job vacancy;
struct job {
	char *name_of_company;  // ������������ �����������.
	char *position;  // ���������.
	char *required_qualification;  // ��������� ������������ (�����������, ������).
	unsigned short int work_experience;  // ���� ������.
	float salary;  // ���������� �����.
};

#define DATA_CNT 10
vacancy data[DATA_CNT] = {
	{ "�����������������", "��������", "������������ ����� ��������� B", 5, 30000 },
	{ "�������������", "���������", "����������� ������ ���������� (���������� �� ������������� \"���. ����, ������ � �����\")", 10, 31000 },
	{ "�������������", "�������������", "��������� ������������ ������ ������� �������� (Power Point, Excel, Word, Outlook)", 3, 29000 },
	{ "�������������", "�������", "���� ������ � ������ �����", 1, 20500 },
	{ "��������������� �����", "��������", "������ ���������� �� ����������� ������������ ����������� ����� ��� ������, ������ ��� � ������ ����� �������� ���������", 2, 25000 },
	{ "����������", "��������", "���� ������ �� ����������� ��������� - ���������", 1, 22000 },
	{ "���������������", "��������-�����������", "���� ������ ���������", 1, 23000 },
	{ "��������������", "�������", "��������� ���� ������ �� ������", 0, 21000 },
	{ "���������������", "�������� �� ��������", "������ �����������", 4, 28000 },
	{ "������������", "������", "������������ ����� ��������� A", 0, 10000 }
};

// ��������� ��� ������ �������� �� �����:
void printjob(vacancy v) {
	printf("\n=== %s, %s ===\n", v.name_of_company, v.position);
	
	printf("����������:\n");
	printf("\t���� ������ �� ����������� ��������� �� %u ���;\n", v.work_experience);
	printf("\t%s.\n", v.required_qualification);

	printf("�������:\n");
	printf("\t����������� ���������� ����� � %.2f ���.\n", v.salary);
	
	printf("\n====================\n");
}

// ��������� ������ ��������� ������� ����:
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
	char client_position[BUFFER_SIZE];  // ��������� �������.
	unsigned short int client_work_experience;  // ���� ������ �������.
	float client_salary;  // ���������� ����� �������.
	
	cyrillic();
	
	printf("���� ���������\n");
	printf("������� �������� � ����� ������������ � �����������:\n");
	
	printf("��������� -> "); 
	fgets(client_position, BUFFER_SIZE, stdin);
	client_position[strcspn(client_position, "\n")] = '\0';
	
	printf("���� ������  -> "); 
	scanf("%hu", &client_work_experience);
	
	printf("���������� ����� -> "); 
	scanf("%f", &client_salary);
	
	printf("\n---------------------------------------------------------------------\n\n");
	
	search(data, DATA_CNT, client_position, client_work_experience, client_salary);

	system("pause");
	return 0;
}

