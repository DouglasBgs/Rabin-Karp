#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utils.c"

#define fileMax 100
#define patternMax 60
#define alphabet 256
#define prime 29

void start();
void search();

void main()
{
  clear();
  start();
}

void search(char text[], char pattern[])
{
  int i, j;
  int hash = 1;
  int matches;
  int patternHash = 0;
  int textHash = 0;
  int patternLength = strlen(pattern);
  int textLength = strlen(text);

  clear();
  printf("Rabin Karp\n\n");

  for (i = 0; i < patternLength - 1; i++)
  {
    hash = (hash * alphabet) % prime;
  }

  for (i = 0; i < patternLength; i++)
  {
    patternHash = (alphabet * patternHash + pattern[i]) % prime;
    textHash = (alphabet * textHash + text[i]) % prime;
  }

  for (i = 0; i <= textLength - patternLength; i++)
  {
    if (patternHash == textHash)
    {
      for (j = 0; j < patternLength; j++)
      {
        if (text[i + j] != pattern[j])
          break;
      }

      if (j == patternLength)
      {
        matches++;
        printf("Padrao encontrado no indice %d \n", i);
      }
    }

    if (i < textLength - patternLength)
    {
      textHash = (alphabet * (textHash - text[i] * hash) + text[i + patternLength]) % prime;

      if (textHash < 0)
        textHash = (textHash + prime);
    }
  }

  if (matches == 0)
    printf("padrao nao encontrado\n");

  getchar();
}

void start()
{
  char file[CHAR_MAX];
  char text[CHAR_MAX];
  char pattern[patternMax];

  printf("Insira o caminho do arquivo: ");
  fgets(file, fileMax, stdin);
  file[strcspn(file, "\n")] = 0;

  clear();

  FILE *arq;
  arq = fopen(file, "r");

  if (arq == NULL)
  {
    printf("Algo de errado nao esta certo, tente novamente!");
    pause();
    clear();
    start();
  }
  else
  {
    fgets(text, sizeof(text), arq);
    fclose(arq);
  }

  printf("Insira o padrao: ");
  fgets(pattern, 100, stdin);
  pattern[strcspn(pattern, "\n")] = 0;

  search(text, pattern);
}
