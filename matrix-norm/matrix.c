#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Вывод матрицы:
void printmat(char* title, float** mat, int m, int n, char* fmt) {
    int i, j;
    printf("%s", title);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(fmt, mat[i][j]);
        }
        printf("\n");
    }
}

// Функции для генерации псевдослучайных чисел:

int randnum() {
    return rand();  // сгенерировать псевдослучайное число в диапазоне от 0 до RAND_MAX.
}

int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // сгенерировать псевдослучайное число в диапазоне [a, b).
}

int main() {
    int i, j, k;
    int m, n;  // размерность mхn исходной матрицы.
    float** mat;  // исходная матрица.
    float** normmat;  // нормированная матрица.
    float rowsum, colsum;
    
    printf("Введите через пробел два числа m и n, задающих размерность исходной матрицы mxn:\n");
    scanf("%d %d", &m, &n);  // ввод значений m и n с клавиатуры.
    
    mat = matalloc(m, n);  // выделение памяти под исходную матрицу.
    normmat = matalloc(m, n);  // выделение памяти под результирующую матрицу.
    
    srand(time(NULL));  // инициализация генератора псевдослучайных чисел.
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = randnumrange(0, 10);  // сгенерировать псевдослучайное число в диапазоне [0, 10).
        }
    }
    
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            
            // Каждый элемент в результирующей матрице вычисляется на основании исходной матрицы,
            // как отношение...
            
            // ...суммы всех других элементов в его строке...
            rowsum = 0; 
            for (k = 0; k < n; k++) {
                if (k == j) {
                    continue;
                }
                rowsum += mat[i][k];
            }
            
            // ...к сумме всех других элементов в его столбце.
            colsum = 0;
            for (k = 0; k < m; k++) {
                if (k == i) {
                    continue;
                }
                colsum += mat[k][j];
            }
            
            // printf("row=%d col=%d rowsum=%.2f colsum=%.2f\n", i, j, rowsum, colsum);  // DEBUG.
            
            normmat[i][j] = rowsum / colsum;
        }
    }
    
    printmat("Вывод исходной матрицы:\n", mat, m, n, "%.0f ");
    printmat("Вывод результирующей матрицы:\n", normmat, m, n, "%.2f ");
    
    matfree(mat, m);  // освобождение памяти выделенной под исходную матрицу.
    matfree(normmat, m);  // освобождение памяти выделенной под результирующую матрицу.
    
    return 0;
}
