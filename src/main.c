#include <stdio.h>
#include <stdlib.h>
#include "indexes.h"

int main(){
	char option;
	char fileName[30], outputPrimary[30], outputSecondary[30];
	char** txt1;
	char** txt2;
	int totalLines1;
	int totalLines2;
	int i, j;
	NRR nrr1;
	NRR nrr2;
	
	/**************** Lista1.txt **************/
	printf("Entre com o nome do arquivo 1 de entrada: ");
	scanf("%s", fileName);
	
	printf("Entre com o nome do arquivo de saída dos índices primarios: ");
	scanf("%s", outputPrimary);

	printf("Entre com o nome do arquivo de saída dos índices secundários: ");
	scanf("%s", outputSecondary);

	do{
		totalLines1 = 0;
		txt1 = createText(fileName, &totalLines1);

		nrr1 = (NRR)malloc(totalLines1 * sizeof(struct nrr)); //Inicializa NRR que salva a posição atual do registro no arquivo.

		for(i = 0; i < totalLines1; i++){
			for(j = 0; j < 6; j++){
				nrr1[i].matricula[j] = txt1[i][j];
			}
			nrr1[i].matricula[6] = '\0';
			nrr1[i].NRR = i;
		}

		nrrHeapsort(nrr1, totalLines1);
		mHeapsort(txt1, totalLines1);

		Link l1 = secondaryIndexes(txt1, totalLines1, outputSecondary);
		
		primaryIndexes(txt1, totalLines1, l1->next, nrr1, outputPrimary);

		destroyText(txt1, totalLines1);
		destroyLink(l1->next);
		free(l1);
		l1 = NULL;
		free(nrr1);

		printf("Deseja modificar o arquivo 1 ou ir para a segunda parte do programa? M/S\n");
		scanf(" %c", &option);
		if(option == 'M'|| option == 'm'){
			modify("lista1.txt");
		}
	}
	while(option != 's' && option != 'S');	
	
	
	/**************** Lista2.txt **************/
	printf("Entre com o nome do arquivo 2 de entrada: ");
	scanf("%s", fileName);

	printf("Entre com o nome do arquivo de saída dos índices primarios: ");
	scanf("%s", outputPrimary);

	printf("Entre com o nome do arquivo de saída dos índices secundários: ");
	scanf("%s", outputSecondary);
	
	do{
		totalLines2 = 0;
		txt2 = createText(fileName, &totalLines2);

		nrr2 = (NRR)malloc(totalLines2 * sizeof(struct nrr));	//Inicializa NRR que salva a posição atual do registro no arquivo.

		for(i = 0; i < totalLines2; i++){
			for(j = 0; j < 6; j++){
				nrr2[i].matricula[j] = txt2[i][j];
			}
			nrr2[i].matricula[6] = '\0';
			nrr2[i].NRR = i;
		}

		nrrHeapsort(nrr2, totalLines2);
		mHeapsort(txt2, totalLines2);

		Link l2 = secondaryIndexes(txt2, totalLines2, outputSecondary);
		
		primaryIndexes(txt2, totalLines2, l2->next, nrr2, outputPrimary);

		destroyText(txt2, totalLines2);
		destroyLink(l2->next);
		free(l2);
		l2 = NULL;
		free(nrr2);

		printf("Deseja modificar o arquivo 2 ou ir para a última parte do programa? M/S\n");
		scanf(" %c", &option);
		if(option == 'M'|| option == 'm'){
			modify("lista2.txt");
		}
	}
	while(option != 's' && option != 'S');

	/*Merge*/
	printf("\nMerge lista1.txt e lista2.txt:\n");
	merge();
	
	return 0;
}