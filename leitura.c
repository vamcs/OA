#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

/*cada i*/
typedef struct itemPrimario_struct
{
	/*Chave Primaria*/
	char* chaveP;
	/*Numero relativo do registro no arquivo original*/
	int NRR;
} itemPrimario;

typedef struct itemSecundario_struct
{
	char* chaveS;
	/**/
	char* chaveP;
} itemSecundario;

/*Nesta estrutura serão armazenadas cada chave primaria o inteiro correspondente a
 *proxima posição do array,ao qual node pertence, que possui a mesma chave secundária*/
typedef struct node
{
	char* chaveP;

	int next;
} node;

/*Nesta estrutura serão armazenadas as chaves secundarias sem
 *repetição acompanhadas do primeiro registro com essa chave secundaria*/
typedef struct indiceSecundario
{
	char* chaveS;

	int posicaoDoPrimeiro;
} indiceSecundario;

bool existeArquivo (char* nomeDoArquivo) {
	FILE *fp;
	fp = fopen(nomeDoArquivo, "r");
	if (fp == NULL) {
		fclose(fp);
		return false;
	}
	else {
		fclose(fp);
		return true;
	}
}

/*Apenas o prototipo da função que ordena as chaves e */
void ordenaPrimario(itemPrimario* itensP, int totalDeRegistros) {

	/*ordenar pelo campo chaveP*/

}

void ordenaSecundario(itemSecundario* itensS, int totalDeRegistros) {

	/*ordenar pelo campo chaveS*/

}

/*1 parametro - posição do primeiro elemenoto adicionado com a referida chave secundaria */
/*2 parametro - array chavesSec*/
/*3 parametro - posicao do elemento de chavesSec que modificar o campo next para que a 
	lista se mantenha ordenada*/
void alteraPonteiroDaListaInvertida(int posicaoDoPrimeiro, node *chavesSec, int posicaoDoDesordenado) {
	node elementoComparado = chavesSec[posicaoDoPrimeiro];
	node elementoAnterior;

	/*enquanto a chaveP na posição `posicaoDoDesordenado` for maior ou igual que a cheveP na
	 *do elementoComparado e houver proximo elemento para se comparar*/
	while (strcmp(chavesSec[posicaoDoDesordenado].chaveP, elementoComparado.chaveP) >= 0
			&& elementoComparado.next != -1) {
		/*salvando a referencia para o anterior*/
		elementoAnterior = elementoComparado;
		/*Atulizando o elemento comparado para o proximo da lsita*/
		elementoComparado = chavesSec[elementoComparado.next];
	}
	/*adicionando o elemento no fim da lista*/
	if (elementoComparado.next == -1) {
		/*coloca -1 no atributo next do elemento chavesSec[posicaoDoDesordenado]*/
		chavesSec[posicaoDoDesordenado].next = elementoComparado.next;
		/*a tributo next do antigo ultimo elemento agora aponta para posicaoDoDesordenado*/
		printf("posicaoDoDesordenado: %d\n", posicaoDoDesordenado);
		elementoComparado.next = posicaoDoDesordenado;
	}
	/*adicionando o elemento entre o inicio e o fim*/
	else {
		/*como o elementoComparado tem chaveP certamente maior que a cheve de
		 * chavesSec[posicaoDoDesordenado] então devemos usar a referencia para o elemento
		 * imediatamete anterior */
		chavesSec[posicaoDoDesordenado].next = elementoAnterior.next; 
		elementoAnterior.next = posicaoDoDesordenado;
	}
}

/*Presumindo que os elementos de itensS já estão ordenados por suas chaves secundarias*/
void criaListaInvertida(itemSecundario* itensS, int totalDeRegistros) {
	/*---itensS é array de elementos com os campos chave primaria(chaveP) e
	 *chave secundaria(chaveS)*/

	/*---chavesSec é o array de elementos com os campos chave primaria e posição no array
	 *do proximo elemento com a mesma chave secundaria (next)*/

	/*---indiceSec é o array de elementos com campo chave secundaria e posicao no array
	 *do primeiro elemento com esta cheve secundaria*/

	/*i e j são inteiros para auxiliar na iteração sobre o array itensS para se
	 *gerar uma lista das chaves secundarias sem repetição*/
	int i, j, nChavesSecUnicas = 0;
	/*Este array de nodes, chavesSec, é uma lista, onde não necessariamnete ocorre 
	 *node[i].next == node[i+1]*/
	node *chavesSec = (node*)malloc(totalDeRegistros * sizeof(node));
	indiceSecundario *indiceSec = malloc(sizeof(indiceSecundario));

	/*adicionando a primeira chave secundaria e a posição do primeiro elemento
	*com esta chave no indiceSec*/
	indiceSec[0].chaveS = itensS[0].chaveS;
	indiceSec[0].posicaoDoPrimeiro = 0;
	nChavesSecUnicas++;


	for (i = 0; i < totalDeRegistros; i++) {
		/*criando um node apartir da chave secundaria itensS[i].chaveS e adicionando ele ao
		 *array chavesSec*/

		chavesSec[i].chaveP = itensS[i].chaveP;

		/*temporariamente atribuindo -1 a posição do próximo elemento com chave
		 *secundaria igual*/
		chavesSec[i].next = -1;

		/*loop para verificar se a chave secundaria ainda não existe no indiceSec*/
		for (j = 0;j < nChavesSecUnicas; j++) {
			/*se as trings são iguais*/
			if (strcmp(indiceSec[j].chaveS, itensS[i].chaveS) == 0) {
				break;
			}
		}
		/*se j for igual a nChavesSecUnicas quer dizer nenhuma vez o break interno ao if
		 *foi executado, ou seja , não exite chave igual a itensS[i].chaveS em indiceSec*/
		if (j == nChavesSecUnicas) {

			nChavesSecUnicas++;
			/*adiconando mais espaço no array de indiceSec*/
			indiceSec = realloc(indiceSec, nChavesSecUnicas * sizeof(indiceSecundario));
			/*adicionando a  nova chave única ao indiceSec*/
			indiceSec[j].chaveS = itensS[i].chaveS;
			printf("2-j:%d\titensS[i].chaveS: %s indiceSec[j].chaveS %s\t\n", j, itensS[i].chaveS, indiceSec[j].chaveS);
			/*O primeiro elemento com essa chave secundaria no array chavesSec
			 * é o elemento corrente, chavesSec[i], sua posição é i*/
			indiceSec[j].posicaoDoPrimeiro = i; 

		}
		else {
			/*a chave secundaria ja existe, entao devemos checar qual o valor adequado
			*para o atributo next*/
			alteraPonteiroDaListaInvertida(indiceSec[nChavesSecUnicas].posicaoDoPrimeiro, chavesSec, i);

		}
	}
	printf("\nVamos imprimir o INDICE SECUNDARIO\n");
	for (i = 0; i < nChavesSecUnicas; i++) {
		printf("%s\t%d\n",indiceSec[i].chaveS,indiceSec[i].posicaoDoPrimeiro);
	}
	printf("\nVamos imprimir a LISTA INVERTIDA\n");
	for (i= 0; i < totalDeRegistros; i++) {
		printf("%s\t%d\n", chavesSec[i].chaveP, chavesSec[i].next);
	}

}

void gravandoIndicePrimario (FILE* arquivoIndiceP) {

}

void granvandoIndiceSecundario (FILE* arquivoIndiceP) {

}


FILE* criaArquivoIndicePrimarioESecundario(FILE** arrayDeArquivos, int numeroDoArquivo) {
	char* nomeArquivoIndiceP1 = "indicePLista1.txt";
	char* nomeArquivoIndiceS1 = "indiceSLista1.txt";
	char* nomeArquivoIndiceP2 = "indicePLista2.txt";
	char* nomeArquivoIndiceS2 = "indiceSLista2.txt";

	FILE* arquivoOriginal = arrayDeArquivos[numeroDoArquivo -1];
	FILE* arquivoIndiceP = (FILE*)malloc(sizeof(FILE));
	FILE* arquivoIndiceS = (FILE*)malloc(sizeof(FILE));

	/*numDoRegistro é usado com contador e ele tb faz referencia a
	 *posição do registro no arquivo original*/
	int numDoRegistro, nCaracteres;
	int INICIAL_SIZE = 30;
	int TAMANHO_REGISTRO = 62;
	itemPrimario *itensP = (itemPrimario*)malloc(INICIAL_SIZE * sizeof(itemPrimario));
	itemSecundario *itensS = (itemSecundario*)malloc(INICIAL_SIZE * sizeof(itemSecundario));
	/*ponteiro que ira receber os registros do
	 *arquivo original um a um*/
	char *registro = (char*)malloc(TAMANHO_REGISTRO * sizeof(char));
	/*colocando o ponteiro no inicio do arquivo*/
	fseek(arquivoOriginal, 0, SEEK_SET);
	/*lendo linhas inteiras do arquivo original*/
	for (numDoRegistro = 0;fscanf(arquivoOriginal, "%[^\n]s", registro) != EOF ;numDoRegistro++) {
		fgetc(arquivoOriginal);
		/*alocando espaco para mais um chave*/
		if (numDoRegistro >= INICIAL_SIZE) {
			itensP = realloc(itensP, numDoRegistro * sizeof(itemPrimario));
			itensS = realloc(itensS, numDoRegistro * sizeof(itemSecundario));
			if (itensS == NULL || itensP == NULL) {
				printf("Memoria contigua insuficiente\n");
				exit(1);
			}
		}
		/*criando chave primaria*/
		itensP[numDoRegistro].chaveP = (char*)malloc(30 * sizeof(char));
		for (nCaracteres = 0 ;nCaracteres < 30; nCaracteres++) {
			itensP[numDoRegistro].chaveP[nCaracteres] = registro[nCaracteres];
		}
		itensP[numDoRegistro].NRR = numDoRegistro;

		/*criando chave secundaria*/
		itensS[numDoRegistro].chaveP = (char*)malloc(30 * sizeof(char));
		itensS[numDoRegistro].chaveP = itensP[numDoRegistro].chaveP;
		/*52 e 53são as posicoes das iniciais correspondentes ao curso, que é
		 *chave secundaria*/
		itensS[numDoRegistro].chaveS = (char*)malloc(2 * sizeof(char));
		itensS[numDoRegistro].chaveS[0] = registro[52];
		itensS[numDoRegistro].chaveS[1] = registro[53];
		/*		printf("%d- %s- %s\n\n", itensP[numDoRegistro].NRR, itensP[numDoRegistro].chaveP,
				itensS[numDoRegistro].chaveS);
*/
	}

	/*TODO: ordenar via heapSort itensP e escreve no arquivo indice: chave seguida da posição*/
	ordenaPrimario(itensP, numDoRegistro);

	/*TODO: ordenar via heapSort itensS*/
	ordenaSecundario(itensS, numDoRegistro);

	/*Passando o array de itens secundários para que seja criada a lista invertida.
	*Aqui a variavel numDoRegistro já é igual ao total de registro no arquivo original*/
	criaListaInvertida(itensS, numDoRegistro);

	/*Gravando no arquivo*/
	if (numeroDoArquivo == 1) {
		arquivoIndiceP = fopen(nomeArquivoIndiceP1, "w");
		gravandoIndicePrimario(arquivoIndiceP);
		arquivoIndiceS = fopen(nomeArquivoIndiceS1, "w");
		granvandoIndiceSecundario(arquivoIndiceS);

		/*colocando no array de arquivos*/
		arrayDeArquivos[2] = arquivoIndiceP;
		arrayDeArquivos[3] = arquivoIndiceS;
	}

	else {
		if (numeroDoArquivo == 2) {
			arquivoIndiceP = fopen(nomeArquivoIndiceP2, "w");
			gravandoIndicePrimario(arquivoIndiceP);

			arquivoIndiceS = fopen(nomeArquivoIndiceS2, "w");
			granvandoIndiceSecundario(arquivoIndiceS);

			/*colocando no array de arquivos*/
			arrayDeArquivos[4] = arquivoIndiceP;
			arrayDeArquivos[5] = arquivoIndiceS;
		}
	}

	/*preparando encerramento do programa*/
	fclose(arquivoOriginal);
	printf("Fim\n");
	return arquivoIndiceP;
}


/*Função chamada no inicio do programa para checar se os arquivos 
 *originais exitem e se os indices já foram criados*/
bool checaExistenciaDosArquivos(FILE **arrayDeArquivos) {
	char* nomeArquivo1 = "lista1.txt";
	char* nomeArquivo2 = "lista2.txt";
	bool existeArquivo1 = false;
	bool existeArquivo2 = false;

	/*lista1*/
	if (!existeArquivo(nomeArquivo1)) {
		printf("Nao encontrado arquivo %s\n", nomeArquivo1);
		exit(1);
	}
	else
		arrayDeArquivos[0] = fopen(nomeArquivo1, "r+");
		existeArquivo1 = true;


	/*lista2*/
	if (!existeArquivo(nomeArquivo2)) {
		printf("Nao encontrado arquivo %s\n", nomeArquivo2);
		exit(1);
	}
	else {
		arrayDeArquivos[1] = fopen(nomeArquivo2, "r+");
		existeArquivo2 = true;
	}

	return (existeArquivo1 && existeArquivo2);
}


int main () {
	int i;
	/*O array de Arquivos foi pensado de forma a obedecer a ordem 
	 *de declaração das constantes na função
	 checaExistenciaDosArquivos*/
	FILE **arrayDeArquivos = (FILE**)malloc(6*sizeof(FILE*));
	/*alocando espaço para cada ponteiro do array*/
	for (i = 0; i < 6; i++) {
		arrayDeArquivos[i] = (FILE*)malloc(sizeof(FILE));
	}
	if (checaExistenciaDosArquivos(arrayDeArquivos)) {
		/*criando os indices do arquivo 1*/
		criaArquivoIndicePrimarioESecundario(arrayDeArquivos, 1);
		/*criando os indices do arquivo 2*/
		criaArquivoIndicePrimarioESecundario(arrayDeArquivos, 2);

	}

	return 0;
}

