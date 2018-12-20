#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>




// ���������:

// ������������ ����� ������� ������:
#define INPUT_STRING_MAX_LEN 100

#define MAX_CHAR 256




// ��������� ������:

struct SuffixTreeNode
{
	// ������ ���������� ����, ����� ��������� ����� ��� ������� ��� �������� ����.
	struct SuffixTreeNode* children[MAX_CHAR];
	
    // ��������� �� ������ ����:
    struct SuffixTreeNode* suffixlink; 
    
    // �������� (start, end) ������ ����� ����� ������� ���� ����������� � ������������ �����.
    // ������ ����� ������ ��������� ��� ����: ���� ������������ ���� � ���� �������� ����.
    // �������� (start, end) ��� ��������� ����� �������� � �������� ����.
    // ��������, ���� ��� ���� � � � ����������� ������ � ��������� (5, 8), �����
    // ������� (5, 8) ����� �������� � ���� �.
    int start; 
    int *end; 
    
    // ������ ����� �������� �� ������ ���������� ��������� ������.
    // �� ����� ���� ���� ����� ��������� �� ������ ���� � ������������ � ������ � ���� �� �������.
    // ������������ ����� �� ���� �� ����� � i-��� ����� ��� ������� �������� ������ ������������ � ������� i.
    // ����� ����� ����� � ���������� �����, ���� � �������� �����.
    
    // ��� �������� ����� �������� ������ �������� ��� ���� �� ����� �� �����:
    int suffixindex;
};
typedef struct SuffixTreeNode Node;




// ���������� ����������:

// ������� ������:
char text[INPUT_STRING_MAX_LEN];

// ������� ������-�������:
char pattern[INPUT_STRING_MAX_LEN];

// �������� ����� ������� ������:
int size = -1;

// ��������� �� �������� ����:
Node *root = NULL;
// ������ ����� ����� 0, ������ ��� ������ ��������.

int *rootend = NULL;

Node *activenode = NULL; 

// activeedge �������������� ��� �� ��� ������, 
// � ��� ������ �� ������� ������:
int activeedge = -1; 

int activelen = 0; 

int leafend = -1; 

// ������� ��������� ��������� �������� � ������:
int remainsuffixcnt = 0; 

// lastnewnode ����� ��������� �� ����� ��������� ���������� ����,
// ��������� ����� ��� suffixlink ������ ��������.
Node* lastnewnode = NULL;

int* splitend = NULL;




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

Node* newnode(int start, int* end) 
{ 
	int i;
	Node* node = (Node*)malloc(sizeof(Node)); 
	
    for (i = 0; i < MAX_CHAR; i++) 
    {
    	node->children[i] = NULL; 
	}
  
    // ��� ��������� ���� suffixlink ����� ����������� �������� NULL.
    // ��� ���������� ����� suffixlink ����� ����������� �������� root 
    // �� ��������� ��� ������� ���������� 
	// � ��� ����������� ����������� �������� ����� ����������.
    node->suffixlink = root; 
    
    node->start = start; 
    node->end = end; 
  
    // suffixindex �� ��������� ��������������� �������� -1,
    // ����������� ������ �������� ��� ������� ����� ����������
    // �� �������������� ������.
	node->suffixindex = -1; 
    
	return node; 
} 

// ����� �����.
// ��������, ���� ��� ���� � � � ����������� ������ � ��������� (5, 8), �����
// ������� (5, 8) ����� �������� � ���� �.
// ����� ����� ����� 8 - 5 + 1 = 4.
int edgelen(Node* n)
{ 
    return *(n->end) - (n->start) + 1; 
}

int walkdown(Node* curr) 
{     
    // ���� activelen ������ ��� ����� �������� �����:
	if (activelen >= edgelen(curr)) 
    {
    	// ��������� activeedge � activelen:
        activeedge += edgelen(curr); 
        activelen -= edgelen(curr); 
        
        // ���������� ��������� ���������� ���� ��������:
        activenode = curr; 
        
        return 1; 
    } 
    return 0; 
} 

void extendsuffixtree(int pos) 
{ 
    leafend = pos; 
  
    // ����������� remainsuffixcnt:
    remainsuffixcnt++; 
  
    // ���������� lastnewnode �������� NULL �� ������ ������ �����,
    // ��� ������, ��� ��� ����������� ���� �������, ����� ���
    // �������� suffixlink ����� �������� �� ������� �����:
	lastnewnode = NULL; 
  
    // ��������� ��� �������� (������� ������ ���� ���������)
    // ���� �� ����� � ������:
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

// ������ ����������� ������ � ��������� �������� ���������.
// ������ ���������� DFS (Depth-first search) ��������.
// ��������� ������ � �������, ��� � ������� �� ��������, 
// ������� � ���, ����� ���� �������� ������, ��������� ��� ��������.
// ���������� ������ ����� ������ � ��� �������� ��������.
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

// ������������ ������ ���������� ��� ���������� ������
// ���� ��������� (post-order) ������ �� �������:
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
	
	// ���������� ����������� ����� ������� ������:
	size = strlen(text);
	
	rootend = (int*)malloc(sizeof(int));
	*rootend = -1;
	
    // ������ ��� ����������� ���� � �������� ��������� � �������� ������ ����� -1
    // �.�. � ���� ��� ������������� ���� �� �������� �� ��� ����� � �����:
    root = newnode(-1, rootend); 
	
	// ������ �������� ����� ����� �������� ����:
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
		printf("���������� ������ ��� ������ '"); 
	    for (i = 0; i < size; i++)
			printf("%c", text[i]); 
	    printf("': "); 
	    for (i = 0; i < size; i++)
			printf("%d ", suffixarray[i]); 
	    printf("\n"); 
	}
} 

// ����� � �������������� ����������� �������:
int search(char* pat, char* txt, int* suffarr, int n, int* resl, int* resr) 
{
	// � ������� ������� suffarr ����� ����� ����� ��� ��������� pat.
	// ���� ����� ����� ��������� pat, ���������� ����� ��� ��������, ������� ���������� �� pat.
	// �� ���� ���������� �� ��������, ��� ��������� ����� ���� � ������. 
	
	// ����� ������� ���������:
    int m = strlen(pat);
    
    // ��������� �������� �����, �� ������� ��������, 
	// ������� ������������� �������� ����������� ������� suffarr:
    int l = 0, r = n - 1;
    while (l <= r) 
    { 
        int mid = l + (r - l) / 2; 
        int res = strncmp(pat, txt + suffarr[mid], m);
        
		// ��� ��������, ��� ������� ��������� pat ����������� �� suffarr[mid] ������� � txt:
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
	// ���������� ������������� �������, ����������� ����� ���������, � ���� ��������� const. 
	// ���� �������� ����� ����� "*", ���� const �����, �� ��� ��������� � �������� ������; ���� ������ � � �������� ���������.
	
	FILE* fp = fopen(inputfilename, "r");
	
	if (fp == NULL)
	{
		printf("������ ��� �������� �����!\n");
		return;
	}
	
	fgets(text, INPUT_STRING_MAX_LEN, fp);
	
	// ��������� ������ ������ ���� ���������� ��� ������:
	text[strcspn(text, "\n")] = '$';
	// ��� ����� ��� ���� ����� �������� �������� � ������� ���������� �������.
	
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
	
    // ������������ ����������� ���������� ������:
    freesuffixtree(root); 
    free(suffixarray);
}

void test()
{
	char inputstr[] = "abcabxabcd$";
	// ��������� ������ ������ ���� ���������� ��� ������.
	// ��� ����� ��� ���� ����� �������� �������� � ������� ���������� �������.
	
	strcpy(text, inputstr);
	printf("���������� ������ ��� ������'%s':\n", inputstr);
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
	    
		printf("������� ������ '%s' ������ �� �������� (������� ���������� � 1):\n", patternstr);
	    printmatches(suffixarray, size, left, right);
	    printf("\n\n");
	}
	
    // ������������ ����������� ���������� ������:
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

