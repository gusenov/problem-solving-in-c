#include <stdio.h>
#include <stdlib.h>

// ��������� ������ ��� �������:
float** matalloc(int m, int n) {
    int i;
    float** mat = malloc(m * sizeof(float*));
    for (i = 0; i < m; i++) { 
        mat[i] = (float*)malloc(n * sizeof(float));
    }
    return mat;
}

// ������������ ������ ���������� ��� �������:
void matfree(float** mat, int m) {
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
void fillmatrand(float** mat, int m, int n) {
	int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = randnumrange(1, 10);  // ������������� ��������������� ����� � ��������� [1, 10).
        }
    }
}

// ����� �������:
void printmat(float** mat, int m, int n, char* fmt) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(fmt, mat[i][j]);
        }
        printf("\n");
    }
}

// ��������� ��������� �������, ������� �� ������� ��������� � ���� ���:
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
    int m, n;  // ����������� m � n �������.
    float** mat;  // �������.

    // ���� �������� m � n � ����������:
    printf("m -> "); scanf("%d", &m);
    printf("n -> "); scanf("%d", &n);

    mat = matalloc(m, n);  // ��������� ������ ��� �������.

	srand(time(NULL));  // ������������� ���������� ��������������� �����.
	fillmatrand(mat, m, n);  // ���������� ������� ���������������� ������.

	printmat(mat, m, n, "%.0f ");  // ����� �� ����� �������� �������.
	
	printf("\n");
	
	zeromat(mat, m, n);  // ��������� ��������� �������, ������� �� ������� ��������� � ���� ���.
	
	printmat(mat, m, n, "%.0f ");  // ����� �� ����� �������������� �������.

	matfree(mat, m);  // ������������ ������ ���������� ��� �������.
	
	system("pause");
	return 0;
}
