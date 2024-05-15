#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX 50
#define INVALID -1

typedef int KEYTYPE;

typedef struct
{
  KEYTYPE key;
} REGISTER;

typedef struct
{
  REGISTER reg;
  int next;
} ELEMENT;

typedef struct
{
  ELEMENT A[MAX];
  int start;
  int available;
} LINKEDLIST;

void startList(LINKEDLIST *list)
{
  int i;
  for (i = 0; i < MAX - 1; i++)
  {
    list->A[i].next = i + 1;
  }
  list->A[MAX - 1].next = INVALID;
  list->start = INVALID;
  list->available = 0;
}

int size(LINKEDLIST *list)
{
  int i = list->start;
  int lenght = 0;

  while (i != INVALID)
  {
    lenght++;
    i = list->A[i].next;
  }
  return lenght;
}

void printList(LINKEDLIST *list)
{
  int i = list->start;
  printf("List: \" ");

  while (i != INVALID)
  {
    printf("%i ", list->A[i].reg.key);
    i = list->A[i].next;
  }

  printf("\"\n");
}

int orderedSequentialSearch(LINKEDLIST *list, KEYTYPE key)
{
  int i = list->start;
  while (i != INVALID && list->A[i].reg.key < key)
  {
    i = list->A[i].next;
  }

  if (i != INVALID && list->A[i].reg.key == key)
  {
    return i;
  }

  return INVALID;
}

int getNode(LINKEDLIST *list)
{
  int result = list->available;

  if (list->available != INVALID)
  {
    list->available = list->A[list->available].next;
  }

  return result;
}

bool insertOrderedListElement(LINKEDLIST *list, REGISTER reg)
{
  if (list->available == INVALID)
  {
    return false;
  }

  int prev = INVALID;
  int i = list->start;
  KEYTYPE key = reg.key;

  while ((i != INVALID) && (list->A[i].reg.key < key))
  {
    prev = i;
    i = list->A[i].next;
  }

  // The element will not be inserted if it already exists
  if (i != INVALID && list->A[i].reg.key == key)
  {
    return false;
  }

  i = getNode(list);
  list->A[i].reg = reg;

  if (prev == INVALID)
  {
    list->A[i].next = list->start;
    list->start = i;
  }
  else
  {
    list->A[i].next = list->A[prev].next;
    list->A[prev].next = i;
  }

  return true;
}

void returnNode(LINKEDLIST *list, int j)
{
  list->A[j].next = list->available;
  list->available = j;
}

bool deleteListElement(LINKEDLIST *list, KEYTYPE key)
{
  int prev = INVALID;
  int i = list->start;

  while ((i != INVALID) && (list->A[i].reg.key < key))
  {
    prev = i;
    i = list->A[i].next;
  }

  if (i == INVALID || list->A[i].reg.key != key)
  {
    return false;
  }

  if (prev == INVALID)
  {
    list->start = list->A[i].next;
  }
  else
  {
    list->A[prev].next = list->A[i].next;
  }

  returnNode(list, i);

  return true;
}

void resetList(LINKEDLIST *list)
{
  startList(list);
}

int main()
{
  REGISTER reg1, reg2, reg3, reg4, reg5;
  LINKEDLIST *list = (LINKEDLIST *)malloc(sizeof(LINKEDLIST));
  reg1.key = 1;
  reg2.key = 4;
  reg3.key = 7;
  reg4.key = 2;
  reg5.key = 5;

  startList(list);

  insertOrderedListElement(list, reg4);
  insertOrderedListElement(list, reg2);
  insertOrderedListElement(list, reg1);
  insertOrderedListElement(list, reg3);
  insertOrderedListElement(list, reg5);

  printList(list);

  printf("Element %i is in position %i.\n", 1, orderedSequentialSearch(list, 1));

  printf("List size: %i.\n", size(list));

  if (deleteListElement(list, 2))
  {
    printf("Element 2 is deleted.\n");
  }
  else
  {
    printf("Unable to delete element.\n");
  }

  printList(list);

  printf("Resetting list...\n");
  resetList(list);

  printf("List size: %i.\n", size(list));

  printf("\n\n\n");
  return 0;
}
