#include <stdio.h>
#include <malloc.h>

int main()
{
  int *y = (int *)malloc(sizeof(int));
  *y = 20;
  int z = sizeof(int);
  printf("*y=%i z=%i", *y, z);

  printf("\n\n");
  return 0;
}
