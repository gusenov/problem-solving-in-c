#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <windows.h>

#ifdef __WIN32__
	#define SIZE_T "%lu"
#else
	#define SIZE_T "%zu"
#endif

// Переход на кириллицу:
void cyrillic() {
	// Эти строки нужны для правильного отображения кириллицы:
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	// Также надо изменить шрифт в консоли на Lucida Console.
	// Для замены шрифта кликаете правой кнопкой на надписи «Командная строка» окна консоли. 
	// В открывшемся меню выбираете «Свойства». 
	// В появившемся окне выбираете вкладку «Шрифт» и там выбираете «Lucida Console». 
}

// Ключевое слово const
// Существует мнемоническое правило, позволяющее легко запомнить, к чему относится const. 
// Надо провести черту через "*", если const слева, то оно относится к значению данных; если справа — к значению указателя.

char* replace_symbolic_constants(const char* str) {
    char* result_string = NULL;  // результирующая строка.
    size_t result_length = 0;  // длина результирующей строки.
    
    int code;  // десятичный код символьной константы.
    size_t code_length;  // количество цифр в десятичном коде.
    
    const char* p = NULL;
    size_t i;
    
    // Определяем размер памяти, который необходимо выделить под результирующую строку:
    p = str;
    while (*p != '\0') {
        if (*p == '\'' && *(p + 2) == '\'') {
            code = *(p + 1);
            
            // Определяем скольно нужно места для хранения десятичного кода вместо символьной константы:
            while (code != 0) {
                result_length++;
                code /= 10;
            }
            
            p += 3;
        } else {
            result_length++;
            p++;
        }
    }
    
    printf("Длина результирующей строки = " SIZE_T "\n", result_length);
    result_string = (char*)malloc( (result_length + 1) * sizeof(char) );  // выделение памяти; +1 для хранения нуль-символа.
    
    // Замена символьных констант на их десятичные коды:
    p = str;
    i = 0;
    while (*p != '\0') {
        if (*p == '\'' && *(p + 2) == '\'') {
            
            // Определяем количество цифр в десятичном коде:
            code = *(p + 1);
            code_length = 0;
            while (code != 0) {
                code_length++;
                code /= 10;
            }
            
            // Перевод символьной константы в десятичный код:
            i += code_length;
            code = *(p + 1);
            while (code != 0) {
                result_string[--i] = (code % 10) + '0';  // записываем цифры в обратном порядке.
                code /= 10;
            }
            i += code_length;
            
            p += 3;
        } else {
            result_string[i++] = *p++;
        }
    }
    
    result_string[i] = '\0';
    
    return result_string;
}

int main() {
	cyrillic();
	
    char* input_string = NULL;  // указатель на массив символов для хранения входной строки.
    size_t input_string_sz = 0;  // переменная для хранения размера input_string.
    
    char* output_string = NULL;  // указатель на результирующую строку.
    
    // ВВОД размер буфера данных для хранения входной строки:
    printf("Введите размер буфера данных для хранения входной строки -> ");
    scanf(SIZE_T, &input_string_sz);
    printf("Размер буфера данных для хранения входной строки = " SIZE_T ".\n", input_string_sz);
    input_string = (char*)malloc(input_string_sz * sizeof(char));
    
    getchar();
    
    // ВВОД строки:
    printf("Введите строку:\n");
    fgets(input_string, input_string_sz, stdin);
    input_string[strcspn(input_string, "\n")] = '\0';  // замена символа "перевода строки" на нуль-символ.
    printf("Вы ввели следующую строку:\n%s\n", input_string);
    
    // ВЫВОД результата:
    output_string = replace_symbolic_constants(input_string);
    printf("В результате замены символьных констант на их десятичные коды получена следующая строка:\n%s\n", output_string);
    
    if (input_string != NULL) {
        free(input_string);
    }
    
    if (output_string != NULL) {
        free(output_string);
    }
    
    system("pause");
    return EXIT_SUCCESS;
}

