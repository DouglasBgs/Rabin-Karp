#include <stdio.h>
#include <string.h>
#include <locale.h> 
#include "utils.c"

#define alfabeto 256
#define prime 30

void bruteForce(char texto[], char frase[]);


void Menu(char texto[], char frase[], char arquivo[])
{
  int opcao;

  do {
    clear();
    printf("Frase: %s\n\n", frase);
    printf("Deseja continuar?\n");
    printf("1 - Continuar\n");
    printf("2 - Sair\n\n");
    printf("Opção: ");
    scanf("%d%*c", &opcao);

    switch(opcao) {
      case 1:
        bruteForce(texto, frase);
      break;
    }
	} while(opcao != 2);
  printf("\n\n Até Logo! \n\n");
}

void startConfig(){
  char arquivo[999999];
  char texto[999999];
  char frase[300];

    printf("- Insira o nome do arquivo: ");
    fgets(arquivo, 999999, stdin);
    arquivo[strcspn(arquivo, "\n")] = 0;

    clear();
  

    FILE *arq;
    arq = fopen(arquivo, "r");
  

    if (arq == NULL)
    {
      printf("Arquivo não encontrado, tente novamente \n");
      system("pause");
      clear();
      startConfig();
    } else {
      fgets(texto, sizeof(texto), arq);
      fclose(arq);
    }

    printf("- Insira a frase que deseja procurar: ");
    fgets(frase, 300, stdin);
    frase[strcspn(frase, "\n")] = 0;
  
  Menu(texto, frase, arquivo);
}

void bruteForce(char texto[], char frase[]) {
  clear();

  printf("--------------------------------------\n");
  printf("------ Algoritimo de força bruta------ \n");
  printf("-------------------------------------- \n\n");

  int acertos;
  int tamTexto = strlen(texto);
  int tamFrase = strlen(frase);

  for (int i = 0; i <= tamTexto - tamFrase; i++) {
    int j;

    // Para o atual index da janela, cheque se existe match
    for (j = 0; j < tamFrase; j++)
      if (texto[i + j] != frase[j]) // Se não existir match, incremente a janela
        break;

    // Se o tamanho total da janela com matches for igual ao do pattern, então mostre o index
    if (j == tamFrase) {
      acertos++;
      printf("Frasse encontrada na coluna %d \n", i);
      pause;
    }
  }

  // Caso não exista matches
  if (acertos == 0)
    printf("Frase não encontrada\n");

  getchar();
};


int main() {
  setlocale(LC_ALL, "Portuguese");
  clear();
  printf("Escreva o nome do arquivo que deseja encontrar a frase\n");
  printf("O arquivo deve ser infomado com a extenção .txt\n\n");
  startConfig();
};