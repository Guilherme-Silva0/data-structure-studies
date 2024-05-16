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
  POINT start;
} LINKEDLIST;

void startList(LINKEDLIST *list)
{
  list->start = NULL;
}

int size(LINKEDLIST *list)
{
  POINT address = list->start;
  int lenght = 0;

  while (address != NULL)
  {
    lenght++;
    address = address->next;
  }
  return lenght;
}

void printList(LINKEDLIST *list)
{
  POINT address = list->start;
  printf("List: \" ");

  while (address != NULL)
  {
    printf("%i ", address->reg.key);
    address = address->next;
  }

  printf("\"\n");
}

POINT sequentialSearch(LINKEDLIST *list, KEYTYPE key)
{
  POINT address = list->start;

  while (address != NULL)
  {
    if (address->reg.key == key)
    {
      return address;
    }

    address = address->next;
  }

  return NULL;
}

POINT orderedSequentialSearch(LINKEDLIST *list, KEYTYPE key)
{
  POINT address = list->start;
  while (address != NULL && address->reg.key < key)
  {
    address = address->next;
  }

  if (address != NULL && address->reg.key == key)
  {
    return address;
  }

  return NULL;
}

POINT sequentialSearchAux(LINKEDLIST *list, KEYTYPE key, POINT *prev)
{
  *prev = NULL;
  POINT current = list->start;

  while ((current != NULL) && (current->reg.key < key))
  {
    *prev = current;
    current = current->next;
  }

  if ((current != NULL) && (current->reg.key == key))
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
  if (prev == NULL)
  {
    current->next = list->start;
    list->start = current;
  }
  else
  {
    current->next = prev->next;
    prev->next = current;
  }

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

  if (prev == NULL)
  {
    list->start = current->next;
  }
  else
  {
    prev->next = current->next;
  }

  free(current);
  return true;
}

void resetList(LINKEDLIST *list)
{
  POINT address = list->start;
  while (address != NULL)
  {
    POINT delete = address;
    address = address->next;
    free(delete);
  }

  list->start = NULL;
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
