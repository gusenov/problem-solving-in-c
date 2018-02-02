#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Для упрощения работы с бинарным типом данных создадим следующую структуру:
typedef struct binary {
   unsigned long len;  // длина буфера.
   char *buffer;       // буфер для временного хранения бинарных данных в оперативной памяти.
} Binary;

// Функция для чтения файлов в бинарном режиме:
Binary readbinary(const char *name) {
    Binary result;
    FILE *file;
    
    // Чтение бинарных данных из файла:
    file = fopen(name, "rb");
    if (!file) {
        fprintf(stderr, "Невозможно открыть файл %s для чтения!\n", name);
        exit(EXIT_FAILURE);  // неудачное выполнении программы.
    }
    fseek(file, 0, SEEK_END);
    result.len = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Динамическое выделение памяти для данных (функция malloc):
    result.buffer = (char *)malloc(result.len + 1);
    if (!result.buffer) {
        fprintf(stderr, "Ошибка памяти!\n");
        fclose(file);
        exit(EXIT_FAILURE);  // неудачное выполнении программы.
    }
    
    fread(result.buffer, result.len, 1, file);
    fclose(file);
    
    return result;
}

// Для того чтобы как-то представить результаты поиска создадим следующую структуру данных:
typedef struct searchresult {
   unsigned long pos;  // позиция начиная с которой найдена искомая последовательность байтов.
   bool notfound;      // если true, то ничего не найдено и значение pos не имеет смысла.
} SearchResult;

// Функция для поиска последовательности байтов tofind в исходных данных data начиная с заданной позиции:
SearchResult search(Binary *data, Binary *tofind, unsigned long startpos) {
    SearchResult result = { 0, true };  // по умолчанию "ничего не найдено".
    unsigned long i, j;
    
    // Простой поиск заданной последовательности данных в бинарном буфере:
    for (i = startpos; i < data->len; i++) {
        for (j = 0; j < tofind->len && i + j < data->len; j++) {
            if (data->buffer[i + j] != tofind->buffer[j]) {
                break;
            }
        }
        if (j == tofind->len) {  // искомая последовательность найдена:
            result.pos = i;
            result.notfound = false;
            break;
        }
    }
    
    return result;
}

// Следующая функция occurrences используют вышеприведенную функцию search для подсчета количества вхождений
// заданной последовательности байтов в исходные данные.
// Данная функция понадобится для вычисления новой длины буфера при замене данных в функции replace.
unsigned long occurrences(Binary *data, Binary *tofind, unsigned long startpos) {
    unsigned long result = 0;  // количество вхождений.
    SearchResult entry = search(data, tofind, 0);
    while (entry.notfound != true) {  // ищем пока не найдем всё:
        result++;
        entry = search(data, tofind, entry.pos + 1);
    }
    return result;
}

// Следующая функция заменяет последовательность байтов tofind на другую последовательность байтов replacedata в исходных данных data.
Binary replace(Binary *data, Binary *tofind, Binary *replacedata) {
    Binary result;
    int i, j;
    
    // Вычисляем размер для буфера в котором будут хранится данные после замены:
    int occurr = occurrences(data, tofind, 0);
    char *buffer = (char *)malloc(data->len - occurr * tofind->len + occurr * replacedata->len);
    
    unsigned long cnt = 0;
    SearchResult entry = search(data, tofind, 0);

    // Замена заданной последовательности данных в бинарном буфере:
    for (i = 0; i < data->len;) {
        if (entry.notfound != true && entry.pos == i) {
            
            // Производим замену:
            for (j = 0; j < replacedata->len; j++) {
                buffer[cnt++] = replacedata->buffer[j];
            }
            
            entry = search(data, tofind, entry.pos + 1);  // ищем следующее вхождение, которое надо заменить.
            i += tofind->len;
        } else {
            buffer[cnt++] = data->buffer[i];
            i++;
        }
    }
    
    result.buffer = buffer;
    result.len = cnt;
    
    return result;
}

// Следующая функция предназначена для записи бинарных данных в файл:
void writebinary(const char *name, Binary *output) {
    FILE *fp = fopen (name, "wb");  // открываем файл.
    if (fp != NULL) {        
        fwrite(output->buffer, output->len, 1, fp);  // пишем бинарные данные.
        fclose(fp);  // закрываем файл.
    } else {
        printf("Невозможно открыть файл %s для записи!\n", name);
        exit(EXIT_FAILURE);
    }
}

// Функция для генерации случайных бинарных данных:
void generate(const char *name, unsigned long s) {
    // Создание буфера для данных:
    Binary generated = { s, (char *)malloc(s + 1) };
    if (!generated.buffer) {
        fprintf(stderr, "Ошибка памяти!\n");
        exit(EXIT_FAILURE);  // неудачное выполнении программы.
    }
    
    for (int i = 0; i < generated.len; i++) {
        unsigned char rdm = rand();
        generated.buffer[i] = rdm;
    }
    
    // Используем ранее написанную функцию для записи случайных данных в файл.
    writebinary(name, &generated);
    
    free(generated.buffer);  // буфер больше не нужен поэтому освобождаем ресурсы.
}

// Главная функция. С неё начинается выполнение программы:
int main(int argc, char **argv) {
    unsigned long i;
    const char *c;  // <-- при таком написании const относится к значению данных, а не к значению указателя.
    
    const char *generaname = NULL;  // переменная для хранения имени результирующего бинарного файла для записи случайных данных.
    unsigned long s;                // размер случайных данных.
    
    Binary data;  // буфер для хранения исходных данных.
    
    Binary tofind;  // буфер для хранения искомых данных.
    
    Binary replacedata;             // буфер для хранения данных, которыми нужно заменить искомые данные.
    Binary output;                  // буфер для хранения результата после замены.
    const char *outputname = NULL;  // переменная для хранения имени результирующего бинарного файла для записи данных с заменами.

    FILE *fp;
    SearchResult entry;
    
    // Если программа запущена без аргументов, то выводим подсказку, как запускать программу:
    if (argc == 1) {
        printf("Примеры запуска программы:\n");
        printf("./text -i data.bin tofind.bin replacedata.bin -o output.bin\n");
        printf("./text -g data.bin -s 10000\n");
        printf("./text -g tofind.bin -s 10\n");
        printf("./text -g replacedata.bin -s 10\n");
        return EXIT_SUCCESS;
    }
    
    // Разбор аргументов командной строки:
    for (i = 1; i < argc; i++) {
        c = argv[i];
        if (*c != '-') continue;
        while (*++c) {
            switch (*c) {
                case 'i':
                    data = readbinary(argv[(i + 1) % argc]);  // бинарный файл с данными.
                    tofind = readbinary(argv[(i + 2) % argc]);  // бинарный файл с данными для поиска.
                    replacedata = readbinary(argv[(i + 3) % argc]);  // бинарный файл с данными для замены.
                    break;
                case 'o':
                    outputname = argv[(i + 1) % argc];  // бинарный файл для записи данных с заменами.
                    break;
                case 'g':
                    generaname = argv[(i + 1) % argc];  // имя файла в который нужно сохранить случайные бинарные данные.
                    break;
                case 's':
                    s = strtoul(argv[(i + 1) % argc], NULL, 10);
                    srand((unsigned int)time(NULL));  // инициализация генератор псевдослучайных чисел.
                    generate(generaname, s);  // вызов функции генерации.
                    return EXIT_SUCCESS;
            }
        }
    }

    // Запись текстового файла с результатами поиска:
    i = 0;
    fp = fopen ("search-results.txt", "w");
    if (fp != NULL) {
        entry = search(&data, &tofind, 0);
        while (entry.notfound == false) {
            fprintf(fp, "pos = %lu\n", entry.pos);
            i++;
            entry = search(&data, &tofind, entry.pos + 1);
        }
        fclose(fp);
    } else {
        printf("Невозможно открыть файл search-results.txt для записи!\n");
        exit(EXIT_FAILURE);
    }
    
    // Поиск и замена заданной последовательности данных в бинарном файле:
    output = replace(&data, &tofind, &replacedata);
    
    // Запись бинарных данных в файл:
    writebinary(outputname, &output);
    
    // Освобождаем занятые ресурсы:
    free(data.buffer);
    free(tofind.buffer);
    free(replacedata.buffer);
    free(output.buffer);
    
    return EXIT_SUCCESS;  // успешное выполнение программы.
}
