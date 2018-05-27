#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MATRIX_SZ 6

// ��������� ������ ��� �������:
int** matalloc(int m, int n) {
    int i;
    int** mat = malloc(m * sizeof(int*));
    for (i = 0; i < m; i++) { 
        mat[i] = (int*)malloc(n * sizeof(int));
    }
    return mat;
}

// ������������ ������ ���������� ��� �������:
void matfree(int** mat, int m) {
    int i;
    for (i = 0; i < m; i++) {
        free(mat[i]);
    }
    free(mat);
}

// ������� ��� ��������� ��������������� �����:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // ������������� ��������������� ����� � ��������� [a, b).
}

// ��������� ��� ���������� ������� ���������������� �������:
void fillmatrand(int** mat, int side, bool symmetric) {
	int i, j;
    for (i = 0; i < side; i++) {
        for (j = 0; j < side; j++) {
            mat[i][j] = randnumrange(1, 10);  // ������������� ��������������� ����� � ��������� [1, 10).
            if (symmetric) {
            	mat[side - j - 1][side - i - 1] = mat[i][j];
			}
        }
    }
}

// ����� �������:
void printmat(int** mat, int m, int n, char* fmt) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(fmt, mat[i][j]);
        }
        printf("\n");
    }
}

// ����������� �������� �� ������� ������������ ������������ �������� ���������:
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
    const int m = MATRIX_SZ, n = MATRIX_SZ;  // ����������� m � n �������.
    int** mat = matalloc(m, n);  // ��������� ������ ��� �������.

	srand(time(NULL));  // ������������� ���������� ��������������� �����.
	fillmatrand(mat, MATRIX_SZ, true);  // ���������� ������� ���������������� ������.

	printmat(mat, m, n, "%4d ");  // ����� �� ����� �������� �������.
	
	printf("\n");
	
	if (issymmetric(mat, MATRIX_SZ)) {
		sqr(mat, MATRIX_SZ);
	}
	
	printmat(mat, m, n, "%4d ");  // ����� �� ����� �������������� �������.
	
	matfree(mat, m);  // ������������ ������ ���������� ��� �������.
	
	system("pause");
	return 0;
}
