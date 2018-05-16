/********************************************
* Primeiro Exercício em C					*
*											*
* Autores: Danillo Neves Souza - 14/0135839 *
*		   Andrei Buslik	   - 11/0024702 *
*          Yan Victor		   - 14/0033599 *
*		   Gustavo Costa	   - 14/0142568 *
*											*
* Disciplina: Software Básico				*
* Professor: Marcelo Ladeira				*
*											*			
* Data: 15/05/2018							*
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alfabeto[91] = { 0 }; /* Vetor global para simular a tabela ASCII Base91 */

/*****************************************************
* Função que recebe um caracter, procura o caracter  *
* no vetor 'alfabeto' e retorna o índice do caracter *
* quando o encontra no vetor.						 *
*****************************************************/

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

/**************************************************************
* Função que preenche o vetor 'alfabeto' com os caracteres    *
* da tabela ASCII Base91 para que seja consultada nas funções *
* de codificação e decodificação.							  *
***************************************************************/

void preencheAlfabeto()
{
		char* aux = malloc(sizeof(char));
		int soma = 0;
		int i;
		for(i = 0; i <= 25; i++)			/* Os índices de 0 à 25 repesentam as 26 letras do alfabeto em maiúsculo */
		{
			alfabeto[i] = 'A' + i;
		}
		for(i = 26; i <= 51; i++)			/* Os índices de 26 à 51 repesentam as 26 letras do alfabeto em minúsculo */
		{
			alfabeto[i] = 'a' + soma;
			soma++;
		}
		soma = 0;
		for(i = 52; i <= 61; i++)			/* Os índices de 52 à 61 repesentam os números de 0 à 9 */
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

/***************************************************
* Função que lê um arquivo texto, decodifica seu   *
* conteúdo a partir da tabela ASCII Base91 e grava *
* o conteúdo decodificado em um arquivo binário.   *
***************************************************/

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

	
	fscanf(fp_txt, "%c", read);						/* Leitura do primeiro caracter a ser decodificado no arquivo texto */
	primeiro_asc = base91(read[0]);                 /* Procura o caracter no vetor que representa a tabela ASCII Base91 */
	fscanf(fp_txt, "%c", read);						/* Leitura do segundo caracter a ser decodificado no arquivo texto */
	segundo_asc = base91(read[0]);                  /* Procura o caracter no vetor que representa a tabela ASCII Base91 */
	original = (91)*(primeiro_asc) + (segundo_asc); /* Obtém número original */
	fprintf(fp_bin, "%x\n", original);	            /* Imprime o número no arquivo binário */
	
	while(!feof(fp_txt))							/* O processo anterior é repetido até que se chegue ao final do arquivo texto */
	{
	 fscanf(fp_txt, "%c", read); 
	 primeiro_asc = base91(read[0]);                 
     fscanf(fp_txt, "%c", read);
	 segundo_asc = base91(read[0]);                  
	 original = (91)*(primeiro_asc) + (segundo_asc); 
	 fprintf(fp_bin, "%x\n", original);	             
	}

	fclose(fp_bin);
	fclose(fp_txt);

	free(bin);
	free(txt);

}

/*********************************************************
* Função que recebe um inteiro e busca no vetor alfabeto *
* o caracter referente ao índice indicado pelo inteiro   *
* passado como argumento.								 *
*********************************************************/

char retorna_caracter(int index){
	return alfabeto[index];
}

/***********************************************
* Função que recebe um vetor de caracteres com *
* 13 bits e converte para um número inteiro.   *
***********************************************/

int bin2int(char read[]){ 
	int inteiro = 0, aux = 1;
	for(int i = 12 ; i >= 0 ; i--){
		if(read[i] == '1')
			inteiro += aux;
		aux * = 2;
	}	
	return inteiro;
}

/***********************************************
* Função que lê um arquivo binário, codifica a *
* informação em números inteiros, converte em  *
* caracteres da tabela ASCII Base91 e grava o  *
* conteúdo codificado em um arquivo texto.	   *
***********************************************/

void codeBin(){ 
	int y1, y2;
	FILE *arqLe,*arqEs;
	char read[13];
	char arquivo[50];
	printf("Digite o nome do arquivo: ");
	scanf("%s", arquivo);

	arqLe = fopen(arquivo, "r+");
	arqEs = fopen("saida.txt", "w+");

	do{	
		for(int i = 0; i < 13 ; i++)
			fscanf(arqLe, "%c", &read[i]);				/* Leitura do caracter no arquivo binário */
		y1 = y2 = bin2int(read);						/* As variáveis y1 e y2 recebem o caracter lido já convertido em inteiro */
		y1 /= 91;										/* A variável y1 recebe o quociente da divisão do número inteiro */
		y2 %= 91;										/* A variável y2 recebe o resto da divisão do número inteiro */
		fprintf(arqEs, "%c ", retorna_caracter(y1));	/* O caracter codificado na variável y1 é escrito no arquivo texto */
		fprintf(arqEs, "%c ", retorna_caracter(y2));    /* O caracter codificado na variável y1 é escrito no arquivo texto */
	}while(!feof(arqLe));
	
	fclose(arqLe);
	fclose(arqEs);
	printf("Code executado com sucesso!!\n\n");
}

/********************************************
* Função de interface de usuário, apresenta *
* as opções de codificação e decodificação  *
* de arquivo ou encerrar o programa.        *
********************************************/

void mainMenu(){

	int inicio = 0;

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
    		codeBin();
    		break;
    	case 2:
    		printf("\nIniciando decodificacao do arquivo texto!\n");
    		decodeTxt();
    		break;
    	case 3:
    		exit(0);
    }
}

/********************************
* Função principal do programa. *
********************************/

int main(int argc, char *argv[])
{

	preencheAlfabeto();

	if(argc == 1){
        printf("\n Nao foi passado nenhum argumento!\n");
        mainMenu();
	}
	
	return 0;
}
