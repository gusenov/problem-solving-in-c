#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 10

// ��������� ��� ���������� ������� ���������� �������:
void fillrandom(int *arr, int sz) {
	int i;
	for (i = 1; i < sz; i += 3) {
		arr[i] = rand();  // ������������� ��������������� ����� � ��������� �� 0 �� RAND_MAX.
		arr[i - 1] = arr[i] - 1;
		if (i + 1 < sz) arr[i + 1] = arr[i - 1];
	}
}

// ��������� ��� ������ ������� �� �����:
void printarr(int *arr, int sz) {
	int i;
	printf("A = [");
	for (i = 0; i < sz; i++) {
		printf("%d", arr[i]);
		printf(i != sz - 1 ? ", " : "");
	}
	printf("]\n");
}

// ������� ��� ������ ������ ������������� �������� � �������:
int maxel(int *arr, int sz) {
	int i, max = 0;
	for (i = 1; i < sz; i++) {
		if (arr[i] > arr[max]) {
			max = i;
		}
	}
	return max;
}

// ������� ��� ���������� ����� ��������� �������, ������������ �� ������������� �� 1:
int sumdiffmax1(int *arr, int sz) {
	int i, max = maxel(arr, sz), sum = 0;
	for (i = 0; i < sz; i++) {
		if (i != max && fabs(arr[i] - arr[max]) == 1) {
			sum += arr[i];
		}
	}
	return sum;
}

int main(int argc, char *argv[]) {
	int A[ARRAY_SIZE];
	int max;
	
	srand(time(NULL));  // ������������� ���������� ��������������� �����.
	fillrandom(A, ARRAY_SIZE);  // ��������� ������ ���������� �������.
	
	printarr(A, ARRAY_SIZE);  // ����� ��������� ������� �� �����.
	
	max = maxel(A, ARRAY_SIZE);  // ����������� ������������� ��������.
	printf("max = %d\n", A[max]);  // ����� ������������� �������� �� �����.
	
	printf("S = %d\n", sumdiffmax1(A, ARRAY_SIZE));  // ����� ����� ��������� �������, ������������ �� ������������� �� 1.
	
	system("pause");
	return 0;
}
