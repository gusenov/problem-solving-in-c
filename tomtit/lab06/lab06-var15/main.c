#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 10

// ������� ��� ��������� ��������������� �����:
int randnumrange(int a, int b) {
    return a + rand() % (b - a);  // ������������� ��������������� ����� � ��������� [a, b).
}

// ��������� ��� ���������� ������� ���������� �������:
void fillrandom(float *arr, int sz) {
	int i, num;
	for (i = 0; i < sz; ++i) {
		num = randnumrange(0, 10);
		arr[i] = i % 2 == 0 ? num : -num;
	}
}

// ��������� ��� ������ ������� �� �����:
void printarr(float *arr, int sz) {
	int i;
	printf("A = [");
	for (i = 0; i < sz; i++) {
		printf("%.2f", arr[i]);
		printf(i != sz - 1 ? ", " : "");
	}
	printf("]\n");
}

// ��������� ��� �������������� ������� �� �������: 
//  - ��� ������������� �������� �������� � �������;
//  - ��� ������������� ��������� � 2 ����;
//  - ������� �������� ��� ���������.
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
	
	srand(time(NULL));  // ������������� ���������� ��������������� �����.
	fillrandom(A, ARRAY_SIZE);  // ��������� ������ ���������� �������.
	
	printarr(A, ARRAY_SIZE);  // ����� ��������� ������� �� �����.
	
	changearr(A, ARRAY_SIZE);  // �������������� �������.
	
	printarr(A, ARRAY_SIZE);  // ����� ��������������� ������� �� �����.
	
	system("pause");
	return 0;
}
