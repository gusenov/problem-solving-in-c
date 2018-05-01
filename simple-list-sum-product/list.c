#include <stdio.h>
#include <stdlib.h>

typedef struct node {
 int data;
 struct node* next;
} NODE;

// Функция для инициализации головы списка:
void init(NODE** head) {
 *head = NULL;
}

// Функция для добавления элементов в список:
NODE* add(NODE* node, int data) {
 NODE* temp = (NODE*)malloc(sizeof(NODE));
 if (temp == NULL) {
  exit(0);  // не хватает оперативной памяти!
 }
 
 temp->data = data;
 temp->next = node;
 node = temp;
 
 return node;
}

// Функция для печати элементов списка:
void print_list(NODE* head) {
 NODE* temp;
 for (temp = head; temp; temp = temp->next) {
  printf("%d", temp->data);
  if (temp->next) {
   printf(" -> ");
  } else {
   printf("\n");
  }
 }
}

// Функция для определения наличия нулевых элементов:
int is_zero_elements(NODE* head) {
 NODE* temp;
 for (temp = head; temp; temp = temp->next) {
  if (temp->data == 0) {
   return 1;
  }
 }
 return 0;
}

// Функция для вычисления произведения элементов списка:
int product(NODE* head) {
 NODE* temp;
 int p = 1;
 for (temp = head; temp; temp = temp->next) {
  p *= temp->data;
 }
 return p;
}

// Функция для вычисления суммы элементов списка:
int sum(NODE* head) {
 NODE* temp;
 int s = 0;
 for (temp = head; temp; temp = temp->next) {
  s += temp->data;
 }
 return s;
}

// Функция для освобождения памяти занятой под список:
NODE* free_list(NODE* head) {
 NODE* tmpPtr = head;
 NODE* followPtr;
 while (tmpPtr != NULL) {
  followPtr = tmpPtr;
  tmpPtr = tmpPtr->next;
  free(followPtr);
 }
 return NULL;
}

// Главная функция:
int main() {
 NODE* head;  // голова списка.
 int idx;  // индекс.
 int cnt;  // начальное количество элементов в списке.
 int val;  // значение элемента списка.
 
 init(&head);
 
 printf("Введите количество элементов в списке: ");
 scanf("%d", &cnt);
 
 printf("Введите целые числа в качестве данных для элементов списка:\n");
 for (idx = 1; idx <= cnt; idx++) {
  scanf("%d", &val);
  head = add(head, val);
 }
 
 printf("Вы ввели следующий список элементов:\n");
 print_list(head);
 
 if (is_zero_elements(head)) {
  printf("В списке есть нулевые элементы.\n");
  printf("Сумма = %d\n", sum(head));
 } else {
  printf("В списке нет нулевых элементы.\n");
  printf("Произведение = %d\n", product(head));
 }
 
 head = free_list(head);
 
 return EXIT_SUCCESS;
}

