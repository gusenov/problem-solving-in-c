#include <stdio.h>  // ВВОД/ВЫВОД.

// Нужно для строковых функций, чтобы сравнить собственные результаты со стандартными:
#include <stdlib.h>  // функция atoi.
#include <string.h>  // функция strlen.

#include <stdbool.h>  // нужно для логического типа данных bool.


// Константы:
#define MAX_BUFFER_SZ 10000  /* размер буфера для хранения вводимой пользователем строки. */


// Функции:

// 1. Определение длины строки:
size_t string_length(const char *s) {  // size_t - это long unsigned int.
    const char *p = s;  // указатель на начало строки.
    
    // Движемся до конца строки.
    // Концом строки считается первый встретившийся специальный нуль-символ.
    while (*p != '\0') p++;
    
    return (size_t)(p - s);
}

// 2. Преобразование строки в целое число:
// Первый символ строки может быть знаком. (код ‘0’ – 48, код ‘9’ – 58).
int string_to_int(const char *str) {
    int idx, len = string_length(str), result = 0;
    bool neg = false;
    if (len > 0) {
        neg = str[0] == '-';  // является ли 1-й символ строки знаком минус?
        idx = (neg || str[0] == '+') ? 1 : 0;
        for (; idx < len; idx++) {
            if (str[idx] >= '0' && str[idx] <= '9') {
                result = result * 10 + (str[idx] - '0');
            }
        }
    }
    return neg ? -result : result;
}

// 3. Преобразование целого числа в строку:
// Число может быть отрицательным. 
char* int_to_string(int num, char *str) {
    int i = 0, j;  // индексы.
    int rem;  // остаток от деления.
    bool neg = num < 0;  // является ли число отрицательным?
    int len;  // длина строки.
    int middle;  // индекс центрального элемента строки.
    char ch;  // символ.
    
    if (neg) num = -num;
    
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Извлечение цифр числа в обратном порядке:
    while (num != 0) {
        rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }
    
    if (neg) str[i++] = '-';
    str[i] = '\0';
    
    len = i;
    // printf("len = %d\n", len);  // отладочный вывод длины получившейся строки.
    
    middle = len / 2;
    // printf("middle = %d\n", middle);  // отладочный вывод индекса центрального элемента получившейся строки.
    
    // Изменение порядок цифр в числе на прямой:
    for (i = 0; i < middle; i++) {
        ch = str[i];
        j = len - i - 1;
        // printf("i=%d <-> j=%d\n", i, j);  // отладочный вывод индексов обмениваемых элементов в формате i=# <-> j=#.
        str[i] = str[j];
        str[j] = ch;
    }
    
    return str;
}

// 4. Удаление передаваемого в качестве параметра функции символа из передаваемой в качестве параметра строки:

// Вариант 1:
// Удалить все вхождения символа ch из строки str:
void delete_char_in_str(char *str, char ch) {
    int i, j;  // индексы.
    size_t len = string_length(str);  // длина строки.
    for (i = 0; i < len; i++) {
        if (str[i] == ch) {
            for (j = i + 1; j < len; j++) {
                str[j - 1] = str[j];
            }
            str[--len] = '\0';
            i--;
        }
    }
}

// Вариант 2:
// Строку src оставить без изменений, а результат удаления всех вхождений символа ch в строку src записать в dst:
char* delete_char(char *dst, const char *src, char ch) {
    int i, j;  // индексы.
    size_t len = string_length(src);  // длина строки.
    for (i = j = 0; i < len; i++) {
        if (src[i] != ch) {
            dst[j++] = src[i];
        }
    }
    dst[j] = '\0';
    return dst;
}

// 5. Добавление передаваемого виде параметра функции символа к передаваемой в качестве параметра строке:

// Вариант 1:
// pos - zero-based индекс, т.е. начинающийся с нуля.
void add_char_to_str(char *str, char ch, int pos) {
    int i;  // индексы.
    size_t len = string_length(str);  // длина строки.
    str[len + 2] = '\0';
    for (i = len + 1; i > pos; i--) {
        str[i] = str[i - 1];
    }
    str[pos] = ch;
}

// Вариант 2:
// Строку src оставить без изменений, а результат удаления всех вхождений символа ch в строку src записать в dst:
// pos - zero-based индекс, т.е. начинающийся с нуля.
char* add_char(char *dst, const char *src, char ch, int pos) {
    int i;
    size_t len = string_length(src);  // длина строки.
    dst[len + 2] = '\0';
    for (i = 0; i <= len; i++) {
        if (i < pos) {
            dst[i] = src[i];
        } else if (i > pos) {
            dst[i] = src[i - 1];
        } else if (i == pos) {
            dst[i] = ch;
        }
    }
    return dst;
}

// Очистка стандартного потока ВВОДА:
void clear_stdin() {
    stdin = freopen(NULL, "r", stdin);
}

// Функция для ввода строки.
void input_string(const char *title, char *buffer, const char *echo) {
    size_t len;  // длина строки.

    printf("%s", title);
    fgets(buffer, MAX_BUFFER_SZ, stdin);  // ввод строки пользователем.
    
    // Удаление символа '\n' из конца строки:
    len = string_length(buffer);
    if ((len > 0) && (buffer[len - 1] == '\n')) {
        buffer[len - 1] = '\0';
    }
    
    printf(echo, buffer);
}

int main() {
    char buffer[MAX_BUFFER_SZ];  // буфер для хранения вводимой пользователем строки.
    char result[MAX_BUFFER_SZ];  // буфер для хранения результатов.
    int num;  // число.
    char ch;  // символ.
    
    
    
    // === Определение длины строки: ===
    
    clear_stdin();
    input_string("Введите любую строку: \n", buffer, "Введенная строка: '%s'\n");
    printf("Длина введенной строки (через написанную функцию string_length): %lu\n", string_length(buffer));
    printf("Проверка (через стандартную функцию strlen): %lu\n\n", strlen(buffer));

    
    
    // === Удаление передаваемого в качестве параметра функции символа из передаваемой в качестве параметра строки: ===
    
    clear_stdin();
    printf("Введите символ для удаления из строки '%s': \n", buffer);
    ch = getchar();
    printf("Результат удаления символа '%c' из строки '%s': \n", ch, buffer);
    
    // Вариант 1 (изменение строки):
    delete_char_in_str(buffer, ch);
    printf("'%s'\n\n", buffer);
    
    // Вариант 2 (строка остается без изменений, результат в переменной result):
    //printf("'%s'\n\n", delete_char(result, buffer, ch));
    
    
    
    // === Добавление передаваемого виде параметра функции символа к передаваемой в качестве параметра строке: ===

    clear_stdin();
    printf("Введите символ и позицию для добавления в строку '%s': \n", buffer);
    scanf("%c %d", &ch, &num);
    printf("Результат добавления символа '%c' в строку '%s' в позицию %d: \n", ch, buffer, num);
    
    // Вариант 1 (изменение строки):
    //add_char_to_str(buffer, ch, num);
    //printf("'%s'\n\n", buffer);
    
    // Вариант 2 (строка остается без изменений, результат в переменной result):
    printf("'%s'\n\n", add_char(result, buffer, ch, num));
    
    
    
    // === Преобразование строки в целое число: ===
    // Первый символ строки может быть знаком. (код ‘0’ – 48, код ‘9’ – 58).
    
    clear_stdin();
    input_string("Введите в качестве строки число: \n", buffer, "Введенное в качестве строки число: '%s'\n");
    printf("Преобразование строки в целое число (через написанную функцию string_to_int): %d\n", string_to_int(buffer));
    printf("Проверка (через стандартную функцию atoi): %d\n\n",  atoi(buffer));
    
    
    
    // === Преобразование целого числа в строку: ===
    // Число может быть отрицательным.
    
    clear_stdin();
    printf("Введите любое число: \n");
    scanf("%d", &num);
    printf("Вы ввели число: %d\n", num);
    int_to_string(num, buffer);
    printf("Преобразование целого числа в строку (через написанную функцию string_to_int): '%s'\n", buffer);
    sprintf(buffer, "%d", num);
    printf("Проверка (через стандартную функцию sprintf): '%s'\n\n", buffer);
    
    
    
    return 0;
}

// Спецификаторы целых чисел для использования в функции printf:
//   %d    int
//   %ld   long int
//   %lld  long long int
//   %lu   unsigned long int
//   %llu  unsigned long long int
