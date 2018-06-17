#include <stdio.h>
#include <math.h>

// Подынтегральная функция:
double InFunction(double x) {
  return x / (1 + pow(x, 4));
}

double CalcIntegral(double a, double b, int n) {
  int i;
  double result, h;

  result = 0;

  h = (b - a) / n;  // шаг сетки.

  for(i = 0; i < n; i++) {
    // Вычисляем в средней точке и добавляем в сумму:
    result += InFunction(a + h * (i + 0.5));
  }

  result *= h;

  return result;
}

int main(void) {
  double a, b, integral;
  int n;

  printf("a -> ");
  scanf("%lf", &a);

  printf("b -> ");
  scanf("%lf", &b);

  printf("n -> ");
  scanf("%d", &n);

  integral = CalcIntegral(0, 2, 500);
  printf("Integral = %lf \n", integral);

  return 0;
}

