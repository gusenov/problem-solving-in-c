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

// Функция movezero переносит все элементы, не рав­ные нулю, сохраняя их порядок, в начало последователь­ности, а нулевые – в конец:
void movezero(int* arr, int n) {
    int i, j;
    
    // Для того чтобы перенести не равный нулю элемент с n-ого места на первое нужно n - 1 итераций:
    for (j = 1; j < n; j++) {
        
        // Данный цикл перемещает очередной 0 в конец массива:
        for (i = 0; i < n - j; i++) {  // n - j это граница дальше которой уже размещены нули.
            if (arr[i] == 0) {
                arr[i] = arr[i + 1];
                arr[i + 1] = 0;
            }
        }
        
        printarr("\nПромежуточный результат:\n", arr, n);
    }
}

int main() {
    int i, n;
    int* arr;
    
    srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
    
    printf("Введите длину последовательности целых чисел:\n");
    scanf("%d", &n);  // ввод значения с клавиатуры.
    
    //n = 10;  // DEBUG
    
    arr = (int*) malloc(n * sizeof(int));  // выделяем память под массив случайных чисел.
    
    for (i = 0; i < n; i++) {
        if (randnum() % 2 == 0)
            arr[i] = 0;
        else
            arr[i] = randnumrange(0, 10);  // сгенерировать псевдослучайное число в диапазоне [0, 10).
    }
    
    // DEBUG:
    //arr[0] = 0; arr[1] = 1; arr[2] = 2; arr[3] = 3; arr[4] = 4; arr[5] = 5; arr[6] = 6; arr[7] = 7; arr[8] = 8; arr[9] = 9;
    //arr[0] = 0; arr[1] = 0; arr[2] = 2; arr[3] = 3; arr[4] = 4; arr[5] = 5; arr[6] = 6; arr[7] = 7; arr[8] = 8; arr[9] = 9;
    //arr[0] = 0; arr[1] = 0; arr[2] = 0; arr[3] = 0; arr[4] = 0; arr[5] = 0; arr[6] = 0; arr[7] = 0; arr[8] = 0; arr[9] = 9;
    
    printarr("\nСгенерированный массив псевдослучайных целочисленных чисел:\n", arr, n);
    
    movezero(arr, n);
    
    printarr("\nРезультирующая последовательность целых чисел:\n", arr, n);
    
    free(arr);
    
    return 0;
}
