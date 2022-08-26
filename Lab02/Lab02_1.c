#include <stdio.h>
#include <stdlib.h>
int main(void)
{
  FILE *ptr_arq; //1-CHAMADA SO - cria variável ponteiro para o arquivo
  char c;

//abrindo o arquivo somente leitura 
  ptr_arq = fopen("arquivo1.txt","r"); //2- CHAMADA SO

  if (ptr_arq == NULL)
  {
    printf("Erro ao tentar abrir o arquivo");
    exit(1);
  }
  printf("Arquivo está sendo lido \n\n");
 

  do
  {  
      //faz a leitura dos caracteres no arquivo 
      c = fgetc(ptr_arq);//3-CHAMADA  SO
      
      //exibe o caracteres na tela
      printf("%c" , c);  
            
  }while (c != EOF);//enquanto não for final de arquivo 
  
    fclose(ptr_arq);//fechando o arquivo //4- chamada SO
  system("pause");
  return(0);
}