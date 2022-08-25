#include <stdio.h>
#include <stdlib.h>

void main()
{
	FILE *fptr1, *fptr2; //1-CHAMADA SO - cria variável ponteiro para o arquivo
	char ch, fname1[20], fname2[20];

	printf("\n\n Cópia de um arquivo com um nome diferente :\n");
	printf("----------------------------------\n");

	printf("Digite o nome do arquivo  :");
	scanf("%s",fname1);

	fptr1=fopen(fname1, "r"); //2-CHAMADA SO - abre o arquivo com tipo leitura
	if(fptr1==NULL)
	{
		printf("Arquivo não encontrado ou erro ao abrir");
		exit(1);
	}
	printf(" Digite um novo nome para o arquivo : ");
	scanf("%s",fname2);
	fptr2=fopen(fname2, "w"); //3-CHAMADA SO - abrindo o arquivo com tipo de abertura apenas escrita
	if(fptr2==NULL)
	{
		printf(" Arquivo não encontrado ou erro ao abrir");
		fclose(fptr1); //4-CHAMADA SO - fecha o arquivo fptr1
		exit(2);
	}
	while(1)
	{
		ch=fgetc(fptr1); //5- CHAMADA SO - faz a leitura dos caracteres no arquivo apontado por fptr1 
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fptr2); //6- CHAMADA SO - faz a escrita dos caracteres no arquivo apontado por fptr2 
		}
	}
	printf(" Arquivo %s  copiado com sucesso no arquivo %s. \n\n",fname1,fname2);
	fclose(fptr1);//7- CHAMADA SO - fechando o arquivo fptr1 
	fclose(fptr2);//8- CHAMADA SO - fechando o arquivo fptr2 
	getchar();
}