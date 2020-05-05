#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pause();
void clear();

void pause()
{
  printf("\n");
  system("PAUSE");
}

void clear()
{
  system("@cls||clear");
}
