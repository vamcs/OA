#include <stdio.h>
#include <stdlib.h>
#include "indexes.h"

char** createText(char* fileName, int* totalLines){
	char aux;		//Variável auxiliar de leitura. Lê '\n' e garante a mudança de linha do ponteiro do arquivo.
	int lineNumber;
	
	/*Inicialização do Arquivo de Entrada*/
	FILE* input = fopen(fileName, "r");
	while(input == NULL){
		printf("Arquivo %s inexistente. Entre com o nome correto.\n", fileName);
		scanf("%s", fileName);
		input = fopen(fileName, "r");
	}
	
	/*Contagem do número de linhas do arquivo de entrada.*/
	while(!feof(input)){
		aux = fgetc(input);
		if(aux == '\n'){
			*totalLines = *totalLines + 1;
		}
	}
	
	/*Volta o ponteiro ao início do arquivo de entrada.*/
	rewind(input);
	
	char** txt = (char**)malloc(*totalLines * sizeof(char*));
	for(lineNumber = 0; lineNumber < *totalLines; lineNumber++){
		txt[lineNumber] = (char*)calloc(1, X * sizeof(char) + 1);	//As linhas possuem X (constante) caracteres.
		fscanf(input, "%[^\n]s", txt[lineNumber]);		//Lê uma linha completa.
		fscanf(input, "%c", &aux);			//Lê '\n'
	}
	
	fclose(input);
	return txt;
}

void destroyText(char** txt, int totalLines){
	int i;
	for(i = 0; i < totalLines; i++){
		free(txt[i]);
	}
	free(txt);
}

void saveText(char* fileName, char** txt, int totalLines){
	int lineNumber;

	/*Inicialização do Arquivo de Saida*/
	FILE* output = fopen(fileName, "w");
	while(output == NULL){
		printf("Arquivo %s inexistente. Entre com o nome correto.\n", fileName);
		scanf("%s", fileName);
		output = fopen(fileName, "w");
	}

	for(lineNumber = 0; lineNumber < totalLines; lineNumber++){
		fprintf(output, "%s\n", txt[lineNumber]);
	}

	fclose(output);
}