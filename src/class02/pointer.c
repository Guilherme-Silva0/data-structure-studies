#include <stdio.h>

int main()
{
  int x = 25;
  int *y = &x;
  *y = 30;

  printf("Current value of x: %i\n", x);

  printf("\n\n\n");
  return 0;
}
