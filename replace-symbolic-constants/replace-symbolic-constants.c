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

// ������� �� ���������:
void cyrillic() {
	// ��� ������ ����� ��� ����������� ����������� ���������:
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	// ����� ���� �������� ����� � ������� �� Lucida Console.
	// ��� ������ ������ �������� ������ ������� �� ������� ���������� ������ ���� �������. 
	// � ����������� ���� ��������� ���������. 
	// � ����������� ���� ��������� ������� ������ � ��� ��������� �Lucida Console�. 
}

// �������� ����� const
// ���������� ������������� �������, ����������� ����� ���������, � ���� ��������� const. 
// ���� �������� ����� ����� "*", ���� const �����, �� ��� ��������� � �������� ������; ���� ������ � � �������� ���������.

char* replace_symbolic_constants(const char* str) {
    char* result_string = NULL;  // �������������� ������.
    size_t result_length = 0;  // ����� �������������� ������.
    
    int code;  // ���������� ��� ���������� ���������.
    size_t code_length;  // ���������� ���� � ���������� ����.
    
    const char* p = NULL;
    size_t i;
    
    // ���������� ������ ������, ������� ���������� �������� ��� �������������� ������:
    p = str;
    while (*p != '\0') {
        if (*p == '\'' && *(p + 2) == '\'') {
            code = *(p + 1);
            
            // ���������� ������� ����� ����� ��� �������� ����������� ���� ������ ���������� ���������:
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
    
    printf("����� �������������� ������ = " SIZE_T "\n", result_length);
    result_string = (char*)malloc( (result_length + 1) * sizeof(char) );  // ��������� ������; +1 ��� �������� ����-�������.
    
    // ������ ���������� �������� �� �� ���������� ����:
    p = str;
    i = 0;
    while (*p != '\0') {
        if (*p == '\'' && *(p + 2) == '\'') {
            
            // ���������� ���������� ���� � ���������� ����:
            code = *(p + 1);
            code_length = 0;
            while (code != 0) {
                code_length++;
                code /= 10;
            }
            
            // ������� ���������� ��������� � ���������� ���:
            i += code_length;
            code = *(p + 1);
            while (code != 0) {
                result_string[--i] = (code % 10) + '0';  // ���������� ����� � �������� �������.
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
	
    char* input_string = NULL;  // ��������� �� ������ �������� ��� �������� ������� ������.
    size_t input_string_sz = 0;  // ���������� ��� �������� ������� input_string.
    
    char* output_string = NULL;  // ��������� �� �������������� ������.
    
    // ���� ������ ������ ������ ��� �������� ������� ������:
    printf("������� ������ ������ ������ ��� �������� ������� ������ -> ");
    scanf(SIZE_T, &input_string_sz);
    printf("������ ������ ������ ��� �������� ������� ������ = " SIZE_T ".\n", input_string_sz);
    input_string = (char*)malloc(input_string_sz * sizeof(char));
    
    getchar();
    
    // ���� ������:
    printf("������� ������:\n");
    fgets(input_string, input_string_sz, stdin);
    input_string[strcspn(input_string, "\n")] = '\0';  // ������ ������� "�������� ������" �� ����-������.
    printf("�� ����� ��������� ������:\n%s\n", input_string);
    
    // ����� ����������:
    output_string = replace_symbolic_constants(input_string);
    printf("� ���������� ������ ���������� �������� �� �� ���������� ���� �������� ��������� ������:\n%s\n", output_string);
    
    if (input_string != NULL) {
        free(input_string);
    }
    
    if (output_string != NULL) {
        free(output_string);
    }
    
    system("pause");
    return EXIT_SUCCESS;
}

