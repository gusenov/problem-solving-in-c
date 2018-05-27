#include <stdio.h>
#include <stdlib.h>

// Выделение памяти под матрицу:
float** matalloc(int m, int n) {
    int i;
    float** mat = malloc(m * sizeof(float*));
    for (i = 0; i < m; i++) { 
        mat[i] = (float*)malloc(n * sizeof(float));
    }
    return mat;
}

// Освобождение памяти выделенной под матрицу:
void matfree(float** mat, int m) {
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
void fillmatrand(float** mat, int m, int n) {
	int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = randnumrange(1, 10);  // сгенерировать псевдослучайное число в диапазоне [1, 10).
        }
    }
}

// Вывод матрицы:
void printmat(float** mat, int m, int n, char* fmt) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(fmt, mat[i][j]);
        }
        printf("\n");
    }
}

// Обнуление элементов матрицы, лежащих на главной диагонали и выше нее:
void zeromat(float** mat, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = n - 1; j >= i; j--) {
        	mat[i][j] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
	int i, j;
    int m, n;  // размерность m х n матрицы.
    float** mat;  // матрица.

    // Ввод значений m и n с клавиатуры:
    printf("m -> "); scanf("%d", &m);
    printf("n -> "); scanf("%d", &n);

    mat = matalloc(m, n);  // выделение памяти под матрицу.

	srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
	fillmatrand(mat, m, n);  // заполнение матрицы псевдослучайными числам.

	printmat(mat, m, n, "%.0f ");  // вывод на экран исходной матрицы.
	
	printf("\n");
	
	zeromat(mat, m, n);  // обнуление элементов матрицы, лежащих на главной диагонали и выше нее.
	
	printmat(mat, m, n, "%.0f ");  // вывод на экран результирующей матрицы.

	matfree(mat, m);  // освобождение памяти выделенной под матрицу.
	
	system("pause");
	return 0;
}
