#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define TEXT_BUFFER_SIZE 1024
#define WORD_BUFFER_SIZE 128

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

void strinput(const char *title, const char *echo, char *str, int sz) {
    printf("%s", title);
	fgets(str, sz, stdin);    
    str[strcspn(str, "\n")] = '\0';
    printf("%s%s\n", echo, str);
}

int wordnoinput() {
	int wordno;
	printf("������� ����� ����� -> ");
	scanf("%d", &wordno);
	return wordno;
}

void printmenu() {
	printf("�������� ����� ����:\n");
	printf("1) ���������, ������ �� ��������� ������ � ����� � ��������� �������;\n");
	printf("2) ������� �� ������ ����� � ��������� �������;\n");
	printf("3) �������������� ����� � ��������� �������;\n");
	printf("4) ���������� ������� ��� ����������� � ������ �������� �����;\n");
	printf("5) ������ �� ������ ����� ������ � �������� �������;\n");
	printf("6) �����.\n");
}

int menu() {
	int choice;
		
	printf("������� ����� ������ ���� -> ");
	scanf("%d", &choice);
	while (getchar() != '\n');
	
	return choice;
}

bool isdelimiter(char ch) {
	switch (ch) {
		// ����������� ���� � �����������:
		case ' ':
		case ',': 
		case '!': 
		case '?': 
		case '.':
			return true;
		default:
			return false;
	}
}

// ���������, ������ �� ��������� ������ � ����� � ��������� �������:
bool istextcontainschar(const char *text, int sz, char ch, int wordno) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	int no = 0;
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			// ������ �����:
			//for (j = a; j <= b; j++) { printf("%c", text[j]); } printf("\n");
						
			if (++no == wordno) {
				for (j = a; j <= b; ++j) { if (text[j] == ch) { return true; } }
				return false;
			}

			a = b = -1;
		}
	}
	
	return false;
}

// ������� �� ������ ����� � ��������� �������:
void deletewordbyno(char *text, int sz, int wordno) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	int no = 0;
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			if (++no != wordno) {
				for (j = a; j <= b; ++j) { printf("%c", text[j]); }
			}

			a = b = -1;
		}
		
		if (isdelimiter(text[i])) {
			printf("%c", text[i]);
		}
	}
	
	printf("\n");
}

// �������������� ����� � ��������� �������:
void dublicatewordbyno(char *text, int sz, int wordno) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j, k;
	int textlen = strlen(text);
	int no = 0;
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			++no;
			
			for (k = 1; k <= 2; k++) {
				for (j = a; j <= b; ++j) { printf("%c", text[j]); }
				if (no != wordno) break; else if (k != 2) printf(" ");
			}

			a = b = -1;
		}
		
		if (isdelimiter(text[i])) {
			printf("%c", text[i]);
		}
	}
	
	printf("\n");
}

// ���������� ������� ��� ����������� � ������ �������� �����:
int countword(const char *text, int textsz, const char *word, int wordsz) {
	int result = 0;
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	int wordlen = strlen(word);
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			
			// ������ �����:
			//for (j = a; j <= b; j++) { printf("%c", text[j]); } printf("\n");
			
			for (j = 0; j < wordlen; ++j) {
				if (word[j] != text[a + j]) {
					break;
				}
			}
			if (j == wordlen) { ++result; }
			
			a = b = -1;
		}
	}
	
	return result;
}

// ������ �� ������ ����� ������ � �������� �������:
void printwordsreverse(const char *text, int sz) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	
	for (i = textlen - 1; i >= 0; --i) {

		if (isdelimiter(text[i])) {
			if (b != -1) { a = i + 1; }
		} else if (b == -1) {
			b = i;
		} else if (i == 0) {
			a = i;
		}
		
		if (a != -1 && b != -1) {
			
			// ������ �����:
			for (j = a; j <= b; ++j) { 
				printf("%c", text[j]);
			};
			
			a = b = -1;
		}
		
		if (isdelimiter(text[i])) {
			printf("%c", text[i]);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	char text[TEXT_BUFFER_SIZE];  // �����.
	char word[WORD_BUFFER_SIZE];  // �����.
	char ch;  // ������.
	bool run = true;

	cyrillic();

	strinput("������� �����:\n", "�� ����� ��������� �����:\n", text, TEXT_BUFFER_SIZE);

	printmenu();
	
	do {
		switch (menu()) {
			case 1:
				printf("������� ������ -> ");
				scanf(" %c", &ch);
				printf(istextcontainschar(text, TEXT_BUFFER_SIZE, ch, wordnoinput()) ? "��\n" : "���\n");
				break;
			case 2:
				deletewordbyno(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 3:
				dublicatewordbyno(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 4:
				strinput("������� �����:\n", "�� ����� �����:\n", word, WORD_BUFFER_SIZE);
				printf("����� %s ����������� � ������ %d ��� (-�).\n", word, countword(text, TEXT_BUFFER_SIZE, word, WORD_BUFFER_SIZE));
				break;
			case 5:
				printwordsreverse(text, TEXT_BUFFER_SIZE);
				break;
			case 6:
				run = false;
				break;
			default:
				break;
		}
	} while (run);

	system("pause");
	return 0;
}
