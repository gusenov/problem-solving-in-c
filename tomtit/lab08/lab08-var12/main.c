#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SZ 25
#define COLS 5

// Функция для генерации псевдослучайных чисел:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // сгенерировать псевдослучайное число в диапазоне [a, b).
}

// Процедура для заполнения массива случайными числами:
void fillrandom(int *arr, int sz) {
	int i, num;
	for (i = 0; i < sz; ++i) {
		arr[i] = randnumrange(0, 10);
	}
}

// Процедура для вывода массива как матрицы на экран:
void printarrasmat(int *arr, int sz, int cols) {
	int i, j;
	for (i = 0; i < sz / cols; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", arr[i * cols + j]);
		}
		printf("\n");
	}
}

// Процедура для транспонирования матрицы:
void transpose(int *arr, int sz, int cols) {
	int i, j, t;
	for (i = 0; i < sz / cols; i++) {
		for (j = i; j < cols; j++) {
			if (i != j) {
				t = arr[i * cols + j];
				arr[i * cols + j] = arr[j * cols + i];
				arr[j * cols + i] = t;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int A[SZ];
	
	srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
	fillrandom(A, SZ);  // заполнить массив случайными числами.
	
	printarrasmat(A, SZ, COLS);  // вывод исходного массива как матрицы на экран.
	
	printf("\n");
	
	transpose(A, SZ, COLS);  // транспонирование матрицы.
	
	printarrasmat(A, SZ, COLS);  // вывод результирующего массива как матрицы на экран.
	
	system("pause");
	return 0;
}
