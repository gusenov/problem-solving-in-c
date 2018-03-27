#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int i, j;
    char str[1024];  // строка символов.
    int cnt[26];  // счетчики строчных букв латинского алфавита.
    char max = '\0';  // буква, которая чаще других встречается в строке.
    
    for (i = 'a'; i <= 'z'; i++) {
        cnt[i - 'a'] = 0;
    }
    
    printf("Введите строку:\n");
    fgets(str, sizeof str, stdin);
    str[strcspn(str, "\n")] = '\0';
    printf("Вы ввели следующую строку:\n%s\n", str);
    
    for (i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            j = str[i] - 'a';
            cnt[j]++;
            
            if (max != '\0') {
                if (cnt[j] > cnt[max - 'a']) {
                    max = str[i];
                }
            } else {
                max = str[i];
            }
            
        }
    }
    
    printf("Количество строчных букв латинского алфавита в строке:\n");
    for (i = 'a'; i <= 'z'; i++) {
        if (cnt[i - 'a'] > 0) {
            printf("%c - %d\n", i, cnt[i - 'a']);
        }
    }
    
    printf("Буква, которая чаще других встречается в строке: %c\n", max);
    
    return 0;
}
