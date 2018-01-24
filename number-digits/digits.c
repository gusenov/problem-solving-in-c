#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int number = -123, // данное число.
        digits_count, // тут будет храниться количество цифр в данном числе.
        digits_sum,   // тут будет храниться сумма цифр данного числа.
        tmp,          // временная переменная.
        power_of_10;  // переменная для хранения степеней десятки.

    printf("Введите число: ");
    scanf("%d", &number);
    
    // Определение количества цифр в числе, а также четности суммы цифр данного числа:
    tmp = abs(number);
    digits_count = digits_sum = 0;
    while (tmp != 0) {
        digits_sum += tmp % 10;
        tmp /= 10;
        digits_count++;
    }
    printf("Количество цифр в числе %d равно = %d\n", number, digits_count);
    printf("Сумма цифр числа %d составляет = %d\n", number, digits_sum);
    if (digits_sum % 2 == 0) {
        printf("Сумма цифр числа %d четна.\n", number);
    } else {
        printf("Сумма цифр числа %d нечетна.\n", number);
    }
    
    // Вывод на экран цифр данного числа:
    printf("Цифры числа %d:\n", number);
    if (number < 0) {  // если число отрицательное, то начиная со старшего разряда:
        tmp = abs(number);
        while (tmp != 0) {
            power_of_10 = (int)pow(10, --digits_count);
            printf("%d\n", (tmp - tmp % power_of_10) / power_of_10);
            tmp %= power_of_10;
        }
    } else {  // в противном случае - начиная с младшего разряда:
        tmp = number;
        while (tmp != 0) {
            printf("%d\n", tmp % 10);
            tmp /= 10;
        }
    }
    
    return 0;
}
