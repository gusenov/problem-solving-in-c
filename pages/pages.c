#include <stdio.h>

#define TEST_MAX_CNT 1000
#define PAGES_MAX_CNT 100
#define QUERY_MAX_CNT 100

int main() {
	int t;  // количество тестов (1 <= t <= TEST_MAX_CNT).
	int n;  // количество страниц в учебнике (2 <= n <= PAGES_MAX_CNT).
	int q;  // количество запросов (1 <= q <= QUERY_MAX_CNT).
	int i;  // страница с номером i.
	int p;  // p-я по порядку из оставшихся страниц.
	
	char queryType;  // тип запроса.
	int test;  // счётчик тестов.
	int query;  // счётчик запросов.
	int page;  // счётчик страниц.
	
	// Массив для хранения состояния страниц:
	//  1 - страница на месте;
	//  0 - страница отсутствует.
	int pages[PAGES_MAX_CNT];
	
	int output[TEST_MAX_CNT][QUERY_MAX_CNT];  // выходные данные.
	// Инициализация массива для выходных данных:
	for (test = 0; test < TEST_MAX_CNT; ++test) {
		for (query = 0; query < QUERY_MAX_CNT; ++query) {
			output[test][query] = -1;
		}
	}
	
	scanf("%d", &t);  // прочитать количество тестов.
	for (test = 0; test < t; ++test) {
		//printf("Test # %d\n", test + 1);  // DEBUG.

		scanf("%d", &n);  // прочитать количество страниц.
		scanf("%d", &q);  // прочитать количество запросов.
		
		// В самом начале все страницы в учебнике присутствуют:
		for (page = 0; page < n; ++page) {
			pages[page] = 1;  // флаг 1 говорит о том, что страница на месте.
		}
		
		// Обработка запросов:
		for (query = 0; query < q; ++query) {
			do {  // считываем тип запроса:
				scanf("%c", &queryType);
			} while (queryType != '-' && queryType != '?');
			
			//printf("\tQuery # %d: %c\n", query + 1, queryType);  // DEBUG.
			
			if (queryType == '-') {  // вырывание страниц:
				scanf("%d", &i);
				
				pages[i - 1] = 0;  // вырывание страницы с номером i.
				
				// Вырывание связанной страницы:
				pages[n - i] = 0;  // n - i + 1 - 1

			} else if (queryType == '?') {  // запрос номера p-й по порядку из оставшихся страниц:
				scanf("%d", &p);
				
				for (page = 0; page < n; ++page) {
					if (pages[page]) {
						--p;
					}
					
					if (!p) {
						output[test][query] = page + 1;
						break;
					}
				}
			}
		}
	}
	
	// Вывод выходных данных:
	for (test = 0; test < t; ++test) {
		for (query = 0; query < QUERY_MAX_CNT; ++query) {
			if (output[test][query] != -1) {
				printf("%d\n", output[test][query]);
			}
		}
	}
	
	return 0;
}

