#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 10

// Функция для генерации псевдослучайных чисел:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // сгенерировать псевдослучайное число в диапазоне [a, b).
}

// Процедура для заполнения массива случайными числами:
void fillrandom(float *arr, int sz) {
	int i, num;
	for (i = 0; i < sz; ++i) {
		num = randnumrange(0, 10);
		arr[i] = i % 2 == 0 ? num : -num;
	}
}

// Процедура для вывода массива на экран:
void printarr(float *arr, int sz) {
	int i;
	printf("A = [");
	for (i = 0; i < sz; i++) {
		printf("%.2f", arr[i]);
		printf(i != sz - 1 ? ", " : "");
	}
	printf("]\n");
}

// Процедура для преобразования массива по правилу: 
//  - все отрицательные элементы возвести в квадрат;
//  - все положительные уменьшить в 2 раза;
//  - нулевые оставить без изменения.
void changearr(float *arr, int sz) {
	int i;
	for (i = 0; i < sz; i++) {
		if (arr[i] < 0) {
			arr[i] *= arr[i];
		} else if (arr[i] > 0) {
			arr[i] /= 2;
		}
	}
}

int main(int argc, char *argv[]) {
	float A[ARRAY_SIZE];
	int max;
	
	srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
	fillrandom(A, ARRAY_SIZE);  // заполнить массив случайными числами.
	
	printarr(A, ARRAY_SIZE);  // вывод исходного массива на экран.
	
	changearr(A, ARRAY_SIZE);  // преобразование массива.
	
	printarr(A, ARRAY_SIZE);  // вывод результирующего массива на экран.
	
	system("pause");
	return 0;
}
