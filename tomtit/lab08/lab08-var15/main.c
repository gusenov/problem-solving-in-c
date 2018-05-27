#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MATRIX_SZ 6

// Выделение памяти под матрицу:
int** matalloc(int m, int n) {
    int i;
    int** mat = malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) { 
        mat[i] = (int*)malloc(n * sizeof(int));
    }
    return mat;
}

// Освобождение памяти выделенной под матрицу:
void matfree(int** mat, int m) {
    int i;
    for (i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Функция для генерации псевдослучайных чисел:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // сгенерировать псевдослучайное число в диапазоне [a, b).
}

// Процедура для заполнения матрицы псевдослучайными числами:
void fillmatrand(int** mat, int side, bool symmetric) {
	int i, j;
    for (i = 0; i < side; i++) {
        for (j = 0; j < side; j++) {
            mat[i][j] = randnumrange(1, 10);  // сгенерировать псевдослучайное число в диапазоне [1, 10).
            if (symmetric) {
            	mat[side - j - 1][side - i - 1] = mat[i][j];
			}
        }
    }
}

// Вывод матрицы:
void printmat(int** mat, int m, int n, char* fmt) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(fmt, mat[i][j]);
        }
        printf("\n");
    }
}

// Определение является ли матрица симметричной относительно побочной диагонали:
bool issymmetric(int** mat, int side) {
    int i, j;
    for (i = 0; i < side; i++) {
        for (j = 0; j < side; j++) {
            if (mat[i][j] != mat[side - j - 1][side - i - 1]) {
            	return false;
			}
        }
    }
    return true;
}

void sqr(int** mat, int side) {
	int i, j;
    for (i = 0; i < side; i++) {
        for (j = 0; j < side; j++) {
            if (i == side - j - 1) {
            	mat[i][j] *= mat[i][j];
			}
        }
    }
}

int main(int argc, char *argv[]) {
    const int m = MATRIX_SZ, n = MATRIX_SZ;  // размерность m х n матрицы.
    int** mat = matalloc(m, n);  // выделение памяти под матрицу.

	srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
	fillmatrand(mat, MATRIX_SZ, true);  // заполнение матрицы псевдослучайными числам.

	printmat(mat, m, n, "%4d ");  // вывод на экран исходной матрицы.
	
	printf("\n");
	
	if (issymmetric(mat, MATRIX_SZ)) {
		sqr(mat, MATRIX_SZ);
	}
	
	printmat(mat, m, n, "%4d ");  // вывод на экран результирующей матрицы.
	
	matfree(mat, m);  // освобождение памяти выделенной под матрицу.
	
	system("pause");
	return 0;
}
