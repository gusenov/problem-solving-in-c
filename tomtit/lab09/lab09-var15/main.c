#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define TEXT_BUFFER_SIZE 1024

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

void strinput(const char *title, const char *echo, char *str, int sz) {
    printf("%s", title);
	fgets(str, sz, stdin);    
    str[strcspn(str, "\n")] = '\0';
    printf("%s%s\n", echo, str);
}

int wordnoinput() {
	int wordno;
	printf("Введите номер слова -> ");
	scanf("%d", &wordno);
	return wordno;
}

void printmenu() {
	printf("Выберите пункт меню:\n");
	printf("1) выдать на печать слова максимальной длины;\n");
	printf("2) удалить из слов имеющих нечетную длину среднюю букву;\n");
	printf("3) проверить есть ли в тексте симметричные слова;\n");
	printf("4) перенести первую букву указанного слова в конец слова;\n");
	printf("5) определить количество слов в тексте, оканчивающихся на заданную букву;\n");
	printf("6) выход.\n");
}

int menu() {
	int choice;
		
	printf("Введите номер пункта меню -> ");
	scanf("%d", &choice);
	while (getchar() != '\n');
	
	return choice;
}

bool isdelimiter(char ch) {
	switch (ch) {
		// Разделители слов в предложении:
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
	
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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

// Выдать на печать слова максимальной длины:
void printmaxlenwords(const char *text, int sz) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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

// Удалить из слов имеющих нечетную длину среднюю букву:
void delmidlet(char *text, int sz) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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
				// Печать слова:
				for (j = a; j <= b; j++) {
					if (j == a + (b - a + 1) / 2 ) continue;
					printf("%c", text[j]);
				}
			} else {
				// Печать слова:
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

// Проверить есть ли в тексте симметричные слова:
bool symmetricwords(const char *text, int sz) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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

// Перенести первую букву указанного слова в конец слова:
void mov1let(char *text, int sz, int wordno) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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

// Определить количество слов в тексте, оканчивающихся на заданную букву:
int countword(const char *text, int sz, const char letter) {
	int result = 0;
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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
			
			// Печать слова:
			//for (j = a; j <= b; j++) { printf("%c", ); } printf("\n");
			
			if (text[b] == letter) { ++result; }
			
			a = b = -1;
		}
	}
	
	return result;
}

int main(int argc, char *argv[]) {
	char text[TEXT_BUFFER_SIZE];  // текст.
	char ch;  // символ.
	bool run = true;

	cyrillic();

	strinput("Введите текст:\n", "Вы ввели следующий текст:\n", text, TEXT_BUFFER_SIZE);

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
				printf(symmetricwords(text, TEXT_BUFFER_SIZE) ? "ДА\n" : "НЕТ\n");
				break;
			case 4:
				mov1let(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 5:
				printf("Введите символ -> ");
				scanf("%c", &ch);
				printf("Количество слов в тексте, оканчивающихся на '%c' = %d\n", ch, countword(text, TEXT_BUFFER_SIZE, ch));
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
