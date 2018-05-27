#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define TEXT_BUFFER_SIZE 1024
#define WORD_BUFFER_SIZE 128

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
	printf("1) проверить, входит ли указанный символ в слово с указанным номером;\n");
	printf("2) удалить из текста слово с указанным номером;\n");
	printf("3) продублировать слово с указанным номером;\n");
	printf("4) определить сколько раз встречается в тексте заданное слово;\n");
	printf("5) выдать на печать слова текста в обратном порядке;\n");
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

// Проверить, входит ли указанный символ в слово с указанным номером:
bool istextcontainschar(const char *text, int sz, char ch, int wordno) {
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
			// Печать слова:
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

// Удалить из текста слово с указанным номером:
void deletewordbyno(char *text, int sz, int wordno) {
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

// Продублировать слово с указанным номером:
void dublicatewordbyno(char *text, int sz, int wordno) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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

// Определить сколько раз встречается в тексте заданное слово:
int countword(const char *text, int textsz, const char *word, int wordsz) {
	int result = 0;
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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
			
			// Печать слова:
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

// Выдать на печать слова текста в обратном порядке:
void printwordsreverse(const char *text, int sz) {
	int a = -1;  // индекс символа являющегося началом слова.
	int b = -1;  // индекс символа являющегося окончанием слова.
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
			
			// Печать слова:
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
	char text[TEXT_BUFFER_SIZE];  // текст.
	char word[WORD_BUFFER_SIZE];  // слово.
	char ch;  // символ.
	bool run = true;

	cyrillic();

	strinput("Введите текст:\n", "Вы ввели следующий текст:\n", text, TEXT_BUFFER_SIZE);

	printmenu();
	
	do {
		switch (menu()) {
			case 1:
				printf("Введите символ -> ");
				scanf(" %c", &ch);
				printf(istextcontainschar(text, TEXT_BUFFER_SIZE, ch, wordnoinput()) ? "ДА\n" : "НЕТ\n");
				break;
			case 2:
				deletewordbyno(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 3:
				dublicatewordbyno(text, TEXT_BUFFER_SIZE, wordnoinput());
				break;
			case 4:
				strinput("Введите слово:\n", "Вы ввели слово:\n", word, WORD_BUFFER_SIZE);
				printf("Слово %s встречается в тексте %d раз (-а).\n", word, countword(text, TEXT_BUFFER_SIZE, word, WORD_BUFFER_SIZE));
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
