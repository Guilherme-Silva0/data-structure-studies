#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX 50

typedef int KEYTYPE;

typedef struct
{
  KEYTYPE key;
} REGISTER;

typedef struct
{
  REGISTER A[MAX + 1];
  int numElements;
} LIST;

void startList(LIST *l)
{
  l->numElements = 0;
}

int size(LIST *l)
{
  return l->numElements;
}

void printList(LIST *l)
{
  int i;
  printf("List: \" ");

  for (i = 0; i < l->numElements; i++)
  {
    printf("%i ", l->A[i].key);
  }

  printf("\"\n");
}

int sequentialSearch(LIST *l, KEYTYPE k)
{
  int i = 0;
  while (i < l->numElements)
  {
    if (l->A[i].key == k)
    {
      return i;
    }

    i++;
  }

  return -1;
}

int sentinelSearch(LIST *l, KEYTYPE k)
{
  int i = 0;
  l->A[l->numElements].key = k;
  while (l->A[i].key != k)
    i++;

  if (i == l->numElements)
    return -1;

  return i;
}

bool insertListElement(LIST *l, REGISTER reg, int i)
{
  int j;

  if ((l->numElements == MAX) || (i < 0) || (i > l->numElements))
  {
    return false;
  }

  for (j = l->numElements; j > i; j--)
  {
    l->A[j] = l->A[j - 1];
  }

  l->A[i] = reg;
  l->numElements++;

  return true;
}

int binarySearch(LIST *l, KEYTYPE k)
{
  int left, right, center;

  left = 0;
  right = l->numElements - 1;

  while (left <= right)
  {
    center = ((left + right) / 2);
    if (l->A[center].key == k)
    {
      return center;
    }

    if (l->A[center].key < k)
    {
      left = center + 1;
    }
    else
    {
      right = center - 1;
    }
  }

  return -1;
}

bool insertOrderedListElement(LIST *l, REGISTER reg)
{
  if (l->numElements >= MAX)
    return false;

  int pos = l->numElements;

  while (pos > 0 && l->A[pos - 1].key > reg.key)
  {
    l->A[pos] = l->A[pos - 1];
    pos--;
  }

  l->A[pos] = reg;
  l->numElements++;
}

bool deleteListElement(LIST *l, KEYTYPE k)
{
  int pos, j;
  pos = binarySearch(l, k);

  if (pos == -1)
  {
    return false;
  }

  for (j = pos; j < l->numElements; j++)
  {
    l->A[j] = l->A[j + 1];
  }

  l->numElements--;
  return true;
}

void resetList(LIST *l)
{
  l->numElements = 0;
}

int main()
{
  REGISTER reg1, reg2, reg3, reg4, reg5;
  LIST *list = (LIST *)malloc(sizeof(LIST));
  reg1.key = 1;
  reg2.key = 2;
  reg3.key = 3;
  reg4.key = 4;
  reg5.key = 5;

  startList(list);
  insertOrderedListElement(list, reg4);
  insertOrderedListElement(list, reg2);
  insertOrderedListElement(list, reg1);
  insertOrderedListElement(list, reg3);
  insertOrderedListElement(list, reg5);

  printList(list);

  printf("Element %i is in position %i.\n", 3, binarySearch(list, 3));

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
