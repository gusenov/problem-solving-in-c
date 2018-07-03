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
	
	scanf("%d", &t);  // прочитать количество тестов.
	for (test = 1; test <= t; ++test) {
		//printf("Test # %d\n", test);  // DEBUG.

		scanf("%d", &n);  // прочитать количество страниц.
		scanf("%d", &q);  // прочитать количество запросов.
		
		// В самом начале все страницы в учебнике присутствуют:
		for (page = 0; page < n; ++page) {
			pages[page] = 1;  // флаг 1 говорит о том, что страница на месте.
		}
		
		// Обработка запросов:
		for (query = 1; query <= q; ++query) {
			do {  // считываем тип запроса:
				scanf("%c", &queryType);
			} while (queryType != '-' && queryType != '?');
			
			//printf("Query # %d: %c\n", query, queryType);  // DEBUG.
			
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
						printf("%d\n", page + 1);
						break;
					}
				}
			}
		}
	}
	
	return 0;
}

