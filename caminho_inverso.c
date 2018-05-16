/*
* Primeiro Exercício em C
* Autor: Danillo Neves Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alfabeto[91] = { 0 };

/*************************************************
Função que recebe um caracter, procura o caracter 
no array 'alfabeto' e retorna o índice do caracter 
quando o encontra no array.
**************************************************/

int base91(char caracter)
{
	int i;
	for(i = 0; i<=90; i++)
	{
		if(alfabeto[i] == caracter){
			return i;
		}
	}
}

/**********************************************************
Função que preenche o array 'alfabeto' com os caracteres 
da tabela ASCII Base91 para que seja consultada nas funções 
de codificação e decodificação.
***********************************************************/

void preencheAlfabeto()
{
		char* aux = malloc(sizeof(char));
		int soma = 0;
		int i;
		for(i = 0; i <= 25; i++)
		{
			alfabeto[i] = 'A' + i;
		}
		for(i = 26; i <= 51; i++)
		{
			alfabeto[i] = 'a' + soma;
			soma++;
		}
		soma = 0;
		for(i = 52; i <= 61; i++)
		{
			alfabeto[i] = '0' + soma;
			soma++;
		}
		soma = 0;

		alfabeto[62] = '!';
		alfabeto[63] = '#';
		alfabeto[64] = '$';
		alfabeto[65] = '>';
		alfabeto[66] = '?';
		alfabeto[67] = '@';
		alfabeto[68] = '[';
		alfabeto[69] = ']';
		alfabeto[70] = '^';
		alfabeto[71] = '_';
		alfabeto[72] = '`';
		alfabeto[73] = '{';
		alfabeto[74] = '|';
		alfabeto[75] = '}';
		alfabeto[76] = '~';
		alfabeto[77] = '"';
		alfabeto[78] = '%';
		alfabeto[79] = '&';
		alfabeto[80] = '(';
		alfabeto[81] = ')';
		alfabeto[82] = '*';
		alfabeto[83] = '+';
		alfabeto[84] = ',';
		alfabeto[85] = '.';
		alfabeto[86] = '/';
		alfabeto[87] = ':';
		alfabeto[88] = ';';
		alfabeto[89] = '<';
		alfabeto[90] = '=';

		free(aux);
}

/**********************************************
Função que lê um arquivo texto, decodifica seu 
conteúdo a partir da tabela ASCII Base91 e grava 
o conteúdo decodificado em um arquivo binário.
************************************************/

void decodeTxt()
{
	char *bin = NULL;
	char *txt = NULL;
	char *read = NULL;

	int original = 0;
	int primeiro_asc = 0;
	int segundo_asc = 0;

	FILE *fp_bin = NULL;
	FILE *fp_txt = NULL;

	bin = (char*) malloc(31*sizeof(char));
		//assert(bin != NULL);
	txt = (char*) malloc(31*sizeof(char));
		//assert(txt != NULL);
	read = (char*) malloc(sizeof(char));
		//assert(read != NULL);

	printf("\nDigite o nome do arquivo texto:\n");
	fgets(txt, 31, stdin);

	strtok(txt, "\n");	/* Retira \n */

	fp_txt = fopen(txt, "r");

    if(fp_txt == NULL)
    {
        printf("\nErro ao abrir arquivo texto! Saindo... \n");
        exit(-1);
    }

	fp_bin = fopen("decode.bin", "wb");

    if(fp_bin == NULL)
    {
        printf("\nErro ao abrir arquivo binario! Saindo... \n");
        exit(-1);
    }

	
	fscanf(fp_txt, "%c", read);
	//printf("\natual: %c\n", read[0]);
	primeiro_asc = base91(read[0]);
	fscanf(fp_txt, "%c", read);
	//printf("\natual: %c\n", read[0]);
	segundo_asc = base91(read[0]);
    //printf("\nOLAAA VEII 1: %d e 2: %d\n", primeiro_asc, segundo_asc);
	original = (91)*(primeiro_asc) + (segundo_asc); /* Obtém número original */
	fprintf(fp_bin, "%x\n", original);	/* Imprime o número no arquivo binário */
	
	while(!feof(fp_txt))
	{
	 fscanf(fp_txt, "%c", read); 
	 primeiro_asc = base91(read[0]);
     fscanf(fp_txt, "%c", read);
	 segundo_asc = base91(read[0]);
	 original = (91)*(primeiro_asc) + (segundo_asc); /* Obtém número original */
     printf("\noriginal: %d\n", original);
	 fprintf(fp_bin, "%x\n", original);	/* Imprime o número no arquivo binário */
	}

	fclose(fp_bin);
	fclose(fp_txt);

	free(bin);
	free(txt);

}

/****************************************
Função de interface de usuário, apresenta 
as opções de codificação e decodificação 
de arquivo ou encerrar o programa.
*****************************************/

void mainMenu(){

	int inicio;

	do
	{
        printf("**********************************");
        printf("\n MENU PRINCIPAL\n");
        printf("\n 1: Codificar arquivo binario para arquivo texto em Base91 ");
        printf("\n 2: Decodificar arquivo texto em Base91 para binario \n");
        printf("\n 3: Sair do programa \n");
        printf("**********************************\n");
        printf("Selecione uma das alternativas: \n");
            scanf("%d", &inicio);
                getchar();
    }while(inicio != 1 && inicio != 2 && inicio != 3);

    switch(inicio)
    {
    	case 1:
    		//codeBin();
    		break;
    	case 2:
    		printf("\nIniciando decodificacao do arquivo texto!\n");
    		decodeTxt();
    		break;
    	case 3:
    		exit(0);
    }
}

/****************************
Função principal do programa.
*****************************/

int main(int argc, char *argv[])
{

	preencheAlfabeto();

	if(argc == 1){
        printf("\n Nao foi passado nenhum argumento!\n");
        mainMenu();
	}
	
	//TODO: DOCUMENTAÇÃO INTERNA

	//system("PAUSE");
	return 0;
}
