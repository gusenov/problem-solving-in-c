#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>




// Константы:

// Максимальная длина входной строки:
#define INPUT_STRING_MAX_LEN 100

#define MAX_CHAR 256




// Структуры данных:

struct SuffixTreeNode
{
	// Каждый внутренний узел, кроме корневого имеет как минимум два дочерних узла.
	struct SuffixTreeNode* children[MAX_CHAR];
	
    // Указатель на другой узел:
    struct SuffixTreeNode* suffixlink; 
    
    // Интервал (start, end) задает ребро через которое узел соединяется с родительским узлом.
    // Каждое ребро задает соединяет два узла: один родительский узел и один дочерний узел.
    // Интервал (start, end) для заданного ребра хранится в дочернем узле.
    // Например, есть два узла А и Б соединенных ребром с индексами (5, 8), тогда
    // индексы (5, 8) будут хранится в узле Б.
    int start; 
    int *end; 
    
    // Каждое ребро является не пустой подстрокой исходного текста.
    // Не может быть двух ребер выходящих из одного узла и начинающихся с одного и того же символа.
    // Конкатенация ребер на пути от корня к i-ому листу даёт суффикс исходной строки начинающийся с позиции i.
    // Ребра могут вести к внутренним узлам, либо к листовым узлам.
    
    // Для листовых узлов хранится индекс суффикса для пути от корня до листа:
    int suffixindex;
};
typedef struct SuffixTreeNode Node;




// Глобальные переменные:

// Входная строка:
char text[INPUT_STRING_MAX_LEN];

// Входная строка-образец:
char pattern[INPUT_STRING_MAX_LEN];

// Реальная длина входной строки:
int size = -1;

// Указатель на корневой узел:
Node *root = NULL;
// Корень может иметь 0, одного или больше потомков.

int *rootend = NULL;

Node *activenode = NULL; 

// activeedge представляется как не сам символ, 
// а его индекс во входной строке:
int activeedge = -1; 

int activelen = 0; 

int leafend = -1; 

// Сколько суффиксов предстоит добавить в дерево:
int remainsuffixcnt = 0; 

// lastnewnode будет указывать на новый созданный внутренний узел,
// ожидающий когда его suffixlink примет значение.
Node* lastnewnode = NULL;

int* splitend = NULL;




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

Node* newnode(int start, int* end) 
{ 
	int i;
	Node* node = (Node*)malloc(sizeof(Node)); 
	
    for (i = 0; i < MAX_CHAR; i++) 
    {
    	node->children[i] = NULL; 
	}
  
    // Для корневого узла suffixlink будет установлено значение NULL.
    // Для внутренних узлов suffixlink будет установлено значение root 
    // по умолчанию при текущем расширении 
	// и при последующих расширениях значение может измениться.
    node->suffixlink = root; 
    
    node->start = start; 
    node->end = end; 
  
    // suffixindex по умолчанию устанавливается значение -1,
    // фактический индекс суффикса для листьев будет установлен
    // на заключительных этапах.
	node->suffixindex = -1; 
    
	return node; 
} 

// Длина ребра.
// Например, есть два узла А и Б соединенных ребром с индексами (5, 8), тогда
// индексы (5, 8) будут хранится в узле Б.
// Длина ребра будет 8 - 5 + 1 = 4.
int edgelen(Node* n)
{ 
    return *(n->end) - (n->start) + 1; 
}

int walkdown(Node* curr) 
{     
    // Если activelen больше чем длина текущего ребра:
	if (activelen >= edgelen(curr)) 
    {
    	// Настроить activeedge и activelen:
        activeedge += edgelen(curr); 
        activelen -= edgelen(curr); 
        
        // Установить следующий внутренний узел активным:
        activenode = curr; 
        
        return 1; 
    } 
    return 0; 
} 

void extendsuffixtree(int pos) 
{ 
    leafend = pos; 
  
    // Увеличиваем remainsuffixcnt:
    remainsuffixcnt++; 
  
    // Установить lastnewnode значение NULL на начале нового этапа,
    // это значит, что нет внутреннего узла ждущего, когда его
    // значение suffixlink будет сброшено на текущем этапе:
	lastnewnode = NULL; 
  
    // Добавлять все суффиксы (которые должны быть добавлены)
    // один за одним в дерево:
    while (remainsuffixcnt > 0) { 
  
        if (activelen == 0) 
            activeedge = pos;
  
        if (activenode->children[text[activeedge]] == NULL) 
        { 
            activenode->children[text[activeedge]] = newnode(pos, &leafend); 
  
            if (lastnewnode != NULL) 
            { 
                lastnewnode->suffixlink = activenode; 
                lastnewnode = NULL; 
            } 
        } 
        else
        { 
            Node* next = activenode->children[text[activeedge]]; 
            if (walkdown(next))
            { 
                continue; 
            } 
            if (text[next->start + activelen] == text[pos]) 
            { 
                if(lastnewnode != NULL && activenode != root) 
                { 
                    lastnewnode->suffixlink = activenode; 
                    lastnewnode = NULL; 
                } 
  
                activelen++; 
                break; 
            } 
  
            splitend = (int*)malloc(sizeof(int)); 
            *splitend = next->start + activelen - 1; 
  
            Node* split = newnode(next->start, splitend); 
            activenode->children[text[activeedge]] = split; 
  
            split->children[text[pos]] = newnode(pos, &leafend); 
            next->start += activelen; 
            split->children[text[next->start]] = next; 
  
            if (lastnewnode != NULL) 
            { 
                lastnewnode->suffixlink = split; 
            } 
  
            lastnewnode = split; 
        } 
  
        remainsuffixcnt--; 
        if (activenode == root && activelen > 0)
        { 
            activelen--; 
            activeedge = pos - remainsuffixcnt + 1; 
        } 
        else if (activenode != root)
        { 
            activenode = activenode->suffixlink; 
        } 
    } 
} 

void print(int i, int j) 
{ 
    int k;
    for (k = i; k <= j; k++)
    {
    	printf("%c", text[k]);
	}
} 

// Печать суффиксного дерева и установка индексов суффиксов.
// Дерево печатается DFS (Depth-first search) способом.
// Стратегия поиска в глубину, как и следует из названия, 
// состоит в том, чтобы идти «вглубь» дерева, насколько это возможно.
// Печатается каждое ребро вместе с его индексом суффикса.
void setsuffixindex(Node* n, int labelheight, bool isprint) 
{ 
    if (n == NULL) return;
  
    if (n->start != -1 && isprint)
    { 
        print(n->start, *(n->end)); 
    }
    
    int leaf = 1; 
    int i; 
    for (i = 0; i < MAX_CHAR; i++) 
    { 
        if (n->children[i] != NULL) 
        { 
            if (leaf == 1 && n->start != -1 && isprint)
				printf(" [%d]\n", n->suffixindex); 
  
            leaf = 0; 
            setsuffixindex(
				n->children[i], 
				labelheight + edgelen(n->children[i]),
				isprint
			); 
        } 
    } 
    
	if (leaf == 1) 
    { 
        n->suffixindex = size - labelheight;
        if (isprint)
        	printf(" [%d]\n", n->suffixindex); 
    } 
} 

// Освобождение памяти выделенной под суффиксное дерево
// путём обратного (post-order) обхода «в глубину»:
void freesuffixtree(Node *n) 
{ 
	int i;
	
    if (n == NULL) return;

    for (i = 0; i < MAX_CHAR; i++) 
    { 
        if (n->children[i] != NULL) 
        { 
            freesuffixtree(n->children[i]); 
        } 
    } 
    
    if (n->suffixindex == -1) free(n->end); 

    free(n); 
} 

void buildsuffixtree(bool isprint)
{
	int i;
	int labelheight = 0;
	
	// Определяем фактическую длину входной строки:
	size = strlen(text);
	
	rootend = (int*)malloc(sizeof(int));
	*rootend = -1;
	
    // Корень это специальный узел у которого начальный и конечный индекс равен -1
    // т.к. у него нет родительского узла из которого бы шло ребро к корню:
    root = newnode(-1, rootend); 
	
	// Первым активным узлом будет корневой узел:
	activenode = root;
	
    for (i = 0; i < size; i++)
        extendsuffixtree(i); 
        
	setsuffixindex(root, labelheight, isprint);
}

void dotraversal(Node* n, int suffixarray[], int* idx) 
{ 
	int i = 0; 
	
    if (n == NULL) return;

    if (n->suffixindex == -1)
    { 
        for (i = 0; i < MAX_CHAR; i++) 
        { 
            if (n->children[i] != NULL) 
            { 
                dotraversal(n->children[i], suffixarray, idx); 
            } 
        } 
    } 

    else if (n->suffixindex > -1 && n->suffixindex < size) 
    { 
        suffixarray[(*idx)++] = n->suffixindex; 
    } 
} 
  
void buildsuffixarray(int suffixarray[], bool isprint) 
{ 
    int i = 0; 

    for(i = 0; i < size; i++) suffixarray[i] = -1; 
    
    int idx = 0; 
    dotraversal(root, suffixarray, &idx); 
    
    if (isprint)
    {
		printf("Суффиксный массив для строки '"); 
	    for (i = 0; i < size; i++)
			printf("%c", text[i]); 
	    printf("': "); 
	    for (i = 0; i < size; i++)
			printf("%d ", suffixarray[i]); 
	    printf("\n"); 
	}
} 

// Поиск с использованием суффиксного массива:
int search(char* pat, char* txt, int* suffarr, int n, int* resl, int* resr) 
{
	// С помощью массива suffarr можно легко найти все подстроки pat.
	// Если нужно найти подстроку pat, достаточно найти все суффиксы, которые начинаются на pat.
	// За счёт сортировки по алфавиту, они находятся рядом друг с другом. 
	
	// Длина искомой подстроки:
    int m = strlen(pat);
    
    // Используя бинарный поиск, мы находим суффиксы, 
	// которым соответствуют элементы суффиксного массива suffarr:
    int l = 0, r = n - 1;
    while (l <= r) 
    { 
        int mid = l + (r - l) / 2; 
        int res = strncmp(pat, txt + suffarr[mid], m);
        
		// Это означает, что искомая подстрока pat встречается на suffarr[mid] символе в txt:
		if (res == 0)
		{
			*resl = *resr = mid;
			while ( (*resl - 1 >= 0) && (strncmp(pat, txt + suffarr[*resl - 1], m) == 0) )
				--(*resl);
			while ( (*resr + 1 < n) && (strncmp(pat, txt + suffarr[*resr + 1], m) == 0) )
				++(*resr);
			
			return mid; 
		}
		
        if (res < 0) r = mid - 1; else l = mid + 1; 
    }
    
    return -1;
} 

int intcompare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

void printmatches(int* suffarr, int n, int left, int right)
{
    if (left >= 0 && left <= right && right < n)
    {
    	int len = right - left + 1;
    	//printf("len = %d\n", len);
    	
    	int* arr = (int*)malloc(sizeof(int) * len);
    	int i; for (i = 0; i < len; ++i) arr[i] = suffarr[left + i];
		qsort(arr, len, sizeof(int), intcompare);
    	for (i = 0; i < len; ++i)
    	{
    		printf("%d", arr[i] + 1);
    		if (i < len - 1) printf(", ");
    	}
		free(arr);
	}
}

void readfromfile(const char* inputfilename)
{
	// Существует мнемоническое правило, позволяющее легко запомнить, к чему относится const. 
	// Надо провести черту через "*", если const слева, то оно относится к значению данных; если справа — к значению указателя.
	
	FILE* fp = fopen(inputfilename, "r");
	
	if (fp == NULL)
	{
		printf("Ошибка при открытии файла!\n");
		return;
	}
	
	fgets(text, INPUT_STRING_MAX_LEN, fp);
	
	// Последний символ должен быть уникальным для строки:
	text[strcspn(text, "\n")] = '$';
	// Это нужно для того чтобы избежать проблемы с неявным суффиксным деревом.
	
	//printf("text = '%s'\n", text);
	
	buildsuffixtree(false);
	
    size--; 
    int* suffixarray = (int*)malloc(sizeof(int) * size); 
    buildsuffixarray(suffixarray, false); 
	
	int cnt = 0, left = -1, right = -1;
	while (fgets(pattern, INPUT_STRING_MAX_LEN, fp) != NULL)
	{
		pattern[strcspn(pattern, "\n")] = '\0';
		//printf("pattern = '%s'\n", pattern);
		
		++cnt;
		
		if (search(pattern, text, suffixarray, size, &left, &right) >= 0)
		{
			printf("%d: ", cnt);
			printmatches(suffixarray, size, left, right);
			printf("\n");
		}
	}
	fclose(fp);
	
    // Освобождение динамически выделенной памяти:
    freesuffixtree(root); 
    free(suffixarray);
}

void test()
{
	char inputstr[] = "abcabxabcd$";
	// Последний символ должен быть уникальным для строки.
	// Это нужно для того чтобы избежать проблемы с неявным суффиксным деревом.
	
	strcpy(text, inputstr);
	printf("Суффиксное дерево для строки'%s':\n", inputstr);
	buildsuffixtree(true);
	printf("\n");
	
    size--; 
    int* suffixarray = (int*)malloc(sizeof(int) * size); 
    buildsuffixarray(suffixarray, true); 
    printf("\n");
    
    int left = -1, right = -1;
    char patternstr[] = "ab";
    if (search(patternstr, text, suffixarray, size, &left, &right) >= 0)
    {
	    printf("left = %d, right = %d\n", left, right);
	    
		printf("Образец строки '%s' найден на индексах (индексы начинаются с 1):\n", patternstr);
	    printmatches(suffixarray, size, left, right);
	    printf("\n\n");
	}
	
    // Освобождение динамически выделенной памяти:
    freesuffixtree(root); 
    free(suffixarray);
    
    system("pause"); 
}

int main(int argc, char *argv[])
{
	cyrillic();
	
	//test();
	readfromfile("input.txt");
	
	return 0;
}

