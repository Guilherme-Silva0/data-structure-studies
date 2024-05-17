#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef int KEYTYPE;

typedef struct
{
  KEYTYPE key;
} REGISTER;

typedef struct aux
{
  REGISTER reg;
  struct aux *next;
} ELEMENT;

typedef ELEMENT *POINT;

typedef struct
{
  POINT head;
} LINKEDLIST;

void startList(LINKEDLIST *list)
{
  list->head = (POINT)malloc(sizeof(ELEMENT));
  list->head->next = list->head;
}

int size(LINKEDLIST *list)
{
  POINT address = list->head->next;
  int lenght = 0;

  while (address != list->head)
  {
    lenght++;
    address = address->next;
  }
  return lenght;
}

void printList(LINKEDLIST *list)
{
  POINT address = list->head->next;
  printf("List: \" ");

  while (address != list->head)
  {
    printf("%i ", address->reg.key);
    address = address->next;
  }

  printf("\"\n");
}

POINT sequentialSearch(LINKEDLIST *list, KEYTYPE key)
{
  POINT address = list->head->next;
  list->head->reg.key = key;
  while (address->reg.key != key)
  {
    address = address->next;
  }

  if (address != list->head)
  {
    return address;
  }

  return NULL;
}

POINT orderedSequentialSearch(LINKEDLIST *list, KEYTYPE key)
{
  POINT address = list->head->next;
  list->head->reg.key = key;
  while (address->reg.key < key)
  {
    address = address->next;
  }

  if (address != list->head && address->reg.key == key)
  {
    return address;
  }

  return NULL;
}

POINT sequentialSearchAux(LINKEDLIST *list, KEYTYPE key, POINT *prev)
{
  *prev = list->head;
  POINT current = list->head->next;
  list->head->reg.key = key;

  while (current->reg.key < key)
  {
    *prev = current;
    current = current->next;
  }

  if ((current != list->head) && (current->reg.key == key))
  {
    return current;
  }

  return NULL;
}

bool insertOrderedListElement(LINKEDLIST *list, REGISTER reg)
{
  POINT prev;
  POINT current = sequentialSearchAux(list, reg.key, &prev);

  // The element will not be inserted if it already exists
  if (current != NULL)
  {
    return false;
  }

  current = (POINT)malloc(sizeof(ELEMENT));
  current->reg = reg;

  current->next = prev->next;
  prev->next = current;

  return true;
}

bool deleteListElement(LINKEDLIST *list, KEYTYPE key)
{
  POINT prev;
  POINT current = sequentialSearchAux(list, key, &prev);
  if (current == NULL)
  {
    return false;
  }

  prev->next = current->next;

  free(current);
  return true;
}

void resetList(LINKEDLIST *list)
{
  POINT address = list->head->next;
  while (address != list->head)
  {
    POINT delete = address;
    address = address->next;
    free(delete);
  }

  list->head->next = list->head;
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

  printf("Element %i is in position %i.\n", 1, orderedSequentialSearch(list, 1)->reg.key);

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
