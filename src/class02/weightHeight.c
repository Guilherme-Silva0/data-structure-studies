#include <stdio.h>
#include <malloc.h>

#define maxHeight 225

typedef struct
{
  int weight;
  int height;
} weightHeight;

int main()
{
  weightHeight *person1 = (weightHeight *)malloc(sizeof(weightHeight));
  person1->weight = 80;
  person1->height = 185;

  printf("Weight: %i, Height: %i. ", person1->weight, person1->height);

  if (person1->height > maxHeight)
  {
    printf("height above maximum\n");
  }
  else
  {
    printf("height below maximum\n");
  }

  printf("\n\n");
  return 0;
}
