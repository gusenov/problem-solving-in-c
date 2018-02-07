#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функции для генерации псевдослучайных чисел:

int randnum() {
    return rand();  // сгенерировать псевдослучайное число в диапазоне от 0 до RAND_MAX.
}

int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // сгенерировать псевдослучайное число в диапазоне [a, b).
}

// Вывод массива:
void printarr(char* title, int* arr, int n) {
    int i;
    printf("%s", title);
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Функция sum производит сложение двух аргументов и возвращает их сумму.
int sum(int a, int b) {
    return a + b;
}

// Функция fold позволяет суммировать все числа в массиве целочисленных чисел с использованием функции sum.
// Функция fold получает в качестве аргументов указатель на исходный массив, размер массива, указатель на функцию sum от двух аргументов.
int fold(int* arr, int n, int (*sumptr)(int, int)) {
    int i;
    int s;  // сумма всех элементов массива.
    
    if (n <= 0) {
        return 0;  // если длина массива 0, то возвращаем 0, т.к. нечего считать.
    } else if (n == 1) {
        return arr[0];  // если длина массива 1, то возвращаем первый и единственный элемент.
    } else {  // если длина массива >= 2, то делаем свертку массива:
        s = arr[0] + arr[1];  // суммируем первые два элемента.
        for (i = 2; i < n; i += 1) {
            s = (*sumptr)(s, arr[i]);  // суммируем уже имеющуюся суммы с очередным элементом.
        }
    }
    
    return s;  // функция fold возвращает сумму всех элементов массива.
}

int main() {
    int i, n, s;
    int* arr;
    
    srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
    
    printf("Введите размер массива целочисленных чисел:\n");
    scanf("%d", &n);  // ввод значений m и n с клавиатуры.
    
    arr = (int*) malloc(n * sizeof(int));  // выделяем память под массив случайных чисел.
    
    for (i = 0; i < n; i++) {
        arr[i] = randnumrange(0, 10);  // сгенерировать псевдослучайное число в диапазоне [0, 10).
    }
    
    printarr("\nСгенерированный массив псевдослучайных целочисленных чисел:\n", arr, n);
    
    printf("\nСумма всех чисел (через функцию fold) в массиве = %d\n", fold(arr, n, &sum));

    // Суммируем элементы массива обыкновенным способом для того чтобы проверить функцию fold.
    // Оба значения должны совпадать.
    s = 0;
    for (i = 0; i < n; i++) {
        s += arr[i];
    }
    printf("\nПроверка! Сумма всех чисел (через цикл for) в массиве = %d\n\n", s);
    
    free(arr);
    
    return 0;
}