#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Процедура для ввода данных пользователем:
void input(double *a, double *b, double *c, double *x0, double *xk, double *deltax) {
	printf("a -> "); scanf("%lf", a);
	printf("b -> "); scanf("%lf", b);
	printf("c -> "); scanf("%lf", c);
	printf("x0 -> "); scanf("%lf", x0);
	printf("xk -> "); scanf("%lf", xk);
	printf("deltax -> "); scanf("%lf", deltax);
}

// Функция для вычисления значения зависимого от x, a, b и c:
double f(double x, double a, double b, double c) {
	if (x < 0 && b != 0) {
		return -a * pow(x, 2.0) + b;
	
	} else if (x > 0 && b == 0) {
		return x / (x - c);

	} else {
		return x / -c;

	}
}

int main(int argc, char *argv[]) {
	double a, b, c, x0, x, xk, deltax;
	
	input(&a, &b, &c, &x0, &xk, &deltax);  // ввод данных.
	
	printf("%24s %24s\n", "x", "F(x, a, b, c)");  // вывод заголовка таблицы.
	
	// Вычисление и вывод значений функции на диапазоне от x0 до xk с шагом deltax:
	x = x0;
	while (x <= xk) {
		printf("%24.2lf %24.2lf\n", x, f(x, a, b, c));
		x += deltax;
	}
	
	system("pause");
	return 0;
}

