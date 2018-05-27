#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SZ 25
#define COLS 5

// ������� ��� ��������� ��������������� �����:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // ������������� ��������������� ����� � ��������� [a, b).
}

// ��������� ��� ���������� ������� ���������� �������:
void fillrandom(int *arr, int sz) {
	int i, num;
	for (i = 0; i < sz; ++i) {
		arr[i] = randnumrange(0, 10);
	}
}

// ��������� ��� ������ ������� ��� ������� �� �����:
void printarrasmat(int *arr, int sz, int cols) {
	int i, j;
	for (i = 0; i < sz / cols; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d ", arr[i * cols + j]);
		}
		printf("\n");
	}
}

// ��������� ��� ���������������� �������:
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
	
	srand(time(NULL));  // ������������� ���������� ��������������� �����.
	fillrandom(A, SZ);  // ��������� ������ ���������� �������.
	
	printarrasmat(A, SZ, COLS);  // ����� ��������� ������� ��� ������� �� �����.
	
	printf("\n");
	
	transpose(A, SZ, COLS);  // ���������������� �������.
	
	printarrasmat(A, SZ, COLS);  // ����� ��������������� ������� ��� ������� �� �����.
	
	system("pause");
	return 0;
}
