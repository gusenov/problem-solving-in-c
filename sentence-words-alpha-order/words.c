#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char sentence[1024];  // данное предложение.
    char *tmp_str;        // временная строка.
    char* word;           // слово.
    int word_cnt;         // количество слов.
    char** words;         // массив слов.
    int i, j;             // счетчики.
    
    printf("Введите предложение:\n");
    fgets(sentence, sizeof sentence, stdin);
    sentence[strcspn(sentence, "\n")] = '\0';
    printf("Вы ввели следующее предложение:\n%s\n", sentence);

    // Подсчет количества слов предложении:
    tmp_str = (char *)malloc((strlen(sentence) + 1) * sizeof(char));  // +1 for the null terminator
    strcpy(tmp_str, sentence);
    word = strtok(tmp_str, " ");
    word_cnt = 0;
    while (word) {
        printf("Слово №%d: %s\n", ++word_cnt, word);
        word = strtok(NULL, " ");
    }
    free(tmp_str);
    printf("Количество слов = %d\n", word_cnt);
    
    // Создание массива слов для последующей сортировки:
    words = malloc(word_cnt * sizeof(char*));
    word = strtok(sentence, " ");
    i = 0;
    while (word) {
        words[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(words[i], word);
        
        for (j = 0; words[i][j] != '\0'; j++) {
            words[i][j] = (char)tolower(words[i][j]);
        }
        
        word = strtok(NULL, " ");
        i++;
    }
    
    // Сортировка массива слов в алфавитном порядке:
    for (j = 0; j < word_cnt -1; j++) {
        for (i = 0; i < word_cnt -1; i++) {
            if (0 < strcmp(words[i], words[i +1])) {
                char* tmp_str = words[i];
                words[i] = words[i + 1];
                words[i + 1] = tmp_str;
            }
        }
    }
    
    printf("Все слова в алфавитном порядке:\n");
    for (i = 0; i < word_cnt; i++) {
        printf("%s\n", words[i]);
    }

    // Освобождение памяти:
    for (i = 0; i < word_cnt; i++) {
        free(words[i]);
    }
    free(words);
    
    return 0;
}
