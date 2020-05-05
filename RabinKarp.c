#include <stdio.h>
#include <string.h>
#include <locale.h> 

#define alfabeto 256
#define prime 30


void clear() {
  system("@cls||clear");
}

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
        rabinKarp(texto, frase);
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
    fgets(arquivo, 9999999, stdin);
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

void rabinKarp(char texto[], char frase[]) {
  system("@cls||clear");
  printf("------------------------ \n");
  printf("------ Rabin Karp ------ \n");
  printf("------------------------ \n\n");

  int i, j;
  int hash = 1;
  int acertos;
  int hashFrase = 0;
  int hashTexto = 0;
  int tamFrase = strlen(frase);
  int tamTexto = strlen(texto);

  // Calcula o hash
  for (i = 0; i < tamFrase - 1; i++)
    hash = (hash * alfabeto) % prime;

  // Calcula o hash do frase e da primeira janela
  for (i = 0; i < tamFrase; i++) {
    hashFrase = (alfabeto * hashFrase + frase[i]) % prime;
    hashTexto = (alfabeto * hashTexto + texto[i]) % prime;
  }

  for (i = 0; i <= tamTexto - tamFrase; i++) {
    // Caso aconteça de match entre hash's, analise cada posição
    if (hashFrase == hashTexto)
    {
      for (j = 0; j < tamFrase; j++) {
        if (texto[i + j] != frase[j])
          break;
      }

      // Se o tamanho total de acertos for igual ao do frase, então mostre o index
      if (j == tamFrase){
        acertos++;
        printf("Texto encontrado na coluna %d \n", i);
        printf("\n\n Pressione qualquer tecla para continuar \n" );
      }
    }

    // Calcula o hash da proxima janela removendo o ultimo index utilizado e adicionado um novo
    if (i < tamTexto - tamFrase) {
      hashTexto = (alfabeto * (hashTexto - texto[i] * hash) + texto[i + tamFrase]) % prime;

      // Caso o valor seja dado como negativo, então ele é convertido com o número primo
      if (hashTexto < 0)
        hashTexto = (hashTexto + prime);
    } 
  }
  // Caso não exista matches
  if (acertos == 0)
  {
    printf("Não existe este trecho de texto no arquivo\n");
    printf("Pressione qualquer tecla para continuar \n");
  }
  getchar();

};

int main() {
  setlocale(LC_ALL, "Portuguese");
  clear();
  printf("Escreva o nome do arquivo que deseja encontrar a frase\n");
  printf("O arquivo deve ser infomado com a extenção .txt\n\n");
  startConfig();
}; 