#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define TEXT_BUFFER_SIZE 1024

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
	printf("1) ������ �� ������ ����� ������������ �����;\n");
	printf("2) ������� �� ���� ������� �������� ����� ������� �����;\n");
	printf("3) ��������� ���� �� � ������ ������������ �����;\n");
	printf("4) ��������� ������ ����� ���������� ����� � ����� �����;\n");
	printf("5) ���������� ���������� ���� � ������, �������������� �� �������� �����;\n");
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

int getmaxlenword(const char *text, int sz) {
	int maxlen = 0;
	
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			if (b - a + 1 > maxlen) {
				maxlen = b - a + 1;
			}

			a = b = -1;
		}
	}
	
	return maxlen;
}

// ������ �� ������ ����� ������������ �����:
void printmaxlenwords(const char *text, int sz) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	int maxlen = getmaxlenword(text, sz);
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
						
			if (b - a + 1 == maxlen) {
				for (j = a; j <= b; j++) { printf("%c", text[j]); } printf("\n");
			}

			a = b = -1;
		}
	}

}

// ������� �� ���� ������� �������� ����� ������� �����:
void delmidlet(char *text, int sz) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {
			
			if ( (b - a + 1) % 2 != 0 ) {
				// ������ �����:
				for (j = a; j <= b; j++) {
					if (j == a + (b - a + 1) / 2 ) continue;
					printf("%c", text[j]);
				}
			} else {
				// ������ �����:
				for (j = a; j <= b; j++) { printf("%c", text[j]); }
			}

			a = b = -1;
		}
		
		if (isdelimiter(text[i])) {
			printf("%c", text[i]);
		}
	}
	
	printf("\n");

}

// ��������� ���� �� � ������ ������������ �����:
bool symmetricwords(const char *text, int sz) {
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	
	for (i = 0; i < textlen; ++i) {

		if (isdelimiter(text[i])) {
			if (a != -1) { b = i - 1; }			
		} else if (a == -1) {
			a = i;
		} else if (i == textlen - 1) {
			b = i;
		}
		
		if (a != -1 && b != -1) {

			for (j = a; j < a + (b - a + 1) / 2; j++) {
				if (text[j] != text[b - (j - a)]) break;
			}
			if (j == a + (b - a + 1) / 2) return true;

			a = b = -1;
		}
	}
	
	return false;
}

// ��������� ������ ����� ���������� ����� � ����� �����:
void mov1let(char *text, int sz, int wordno) {
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
			if (++no == wordno) {
				for (j = a + 1; j <= b; ++j) { printf("%c", text[j]); }
				printf("%c", text[a]);
			} else {
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

// ���������� ���������� ���� � ������, �������������� �� �������� �����:
int countword(const char *text, int sz, const char letter) {
	int result = 0;
	int a = -1;  // ������ ������� ����������� ������� �����.
	int b = -1;  // ������ ������� ����������� ���������� �����.
	int i, j;
	int textlen = strlen(text);
	
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
			//for (j = a; j <= b; j++) { printf("%c", ); } printf("\n");
			
			if (text[b] == letter) { ++result; }
			
			a = b = -1;
		}
	}
	
	return result;
}

int main(int argc, char *argv[]) {
	char text[TEXT_BUFFER_SIZE];  // �����.
	char ch;  // ������.
	bool run = true;

	cyrillic();

	strinput("������� �����:\n", "�� ����� ��������� �����:\n", text, TEXT_BUFFER_SIZE);

	printmenu();

	do {
		switch (menu()) {
			case 1:
				printmaxlenwords(text, TEXT_BUFFER_SIZE);
				break;
			case 2:
				delmidlet(text, TEXT_BUFFER_SIZE);
				break;
			case 3:
				printf(symmetricwords(text, TEXT_BUFFER_SIZE) ? "��\n" : "���\n");
				break;
			case 4:
				mov1let(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 5:
				printf("������� ������ -> ");
				scanf("%c", &ch);
				printf("���������� ���� � ������, �������������� �� '%c' = %d\n", ch, countword(text, TEXT_BUFFER_SIZE, ch));
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
