#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

#define X 62  //Número de caracteres por linha das listas
#define Y1 19 //Número inicial de linhas das listas1.txt
#define Y2 22 //Número inicial de linhas das listas2.txt

int main(){
	int i = 0;
	int j = 0;
	int flag = 0;
	int lineNumber;
	char aux;
	char index[30];
	char* line = (char*)malloc(X * sizeof(char));
	//char* index2 = (char*)malloc(30 * sizeof(char));
	
	/*Inicialização dos Arquivos de Entrada*/
	FILE* input[2];
	input[0] = fopen("lista1.txt", "r");
	input[1] = fopen("lista2.txt", "r");
	if(input[0] == NULL || input[0] == NULL){
		printf("Arquivos inexistentes. Stop.\n");
		exit(1);
	}
	
	/*Inicialização dos Arquivos de Saída*/
	FILE* output[2];
	output[0] = fopen("indicelista1.ind", "w"); 
	output[1] = fopen("indicelista2.ind", "w"); 
	
	for(lineNumber = 0;  lineNumber < Y1; lineNumber++){
		fscanf(input[0], "%[^\n]s", line);
		fscanf(input[0], "%c", &aux);
		while(j < 30 && i < X){
			if(line[i] != ' ' || flag >= 2){
				index[j] = line[i];
				i++;
				j++;
				flag = 0;
			}
			else
				i++;
				flag++;
		}
		
		if(j < 30){
			index[j] = ' ';
			j++;
		}
		index[30] = '\0';
		
		fprintf(output[0], "%s %d\n", index, lineNumber);
		i = 0;
		j = 0;
	}
	
	printf("\n");
	
	for(lineNumber = 0;  lineNumber < Y2; lineNumber++){
		fscanf(input[1], "%[^\n]s", line);
		fscanf(input[1], "%c", &aux);
		while(j < 30 && i < X){
			if(line[i] != ' ' || flag >= 2){
				index[j] = line[i];
				i++;
				j++;
				flag = 0;
			}
			else
				i++;
				flag++;
		}
		
		if(j < 30){
			index[j] = ' ';
			j++;
		}
		
		index[30] = '\0';
		
		fprintf(output[1], "%s %d\n", index, lineNumber);
		i = 0;
		j = 0;
	}
	
	free(line);
	fclose(input[0]);
	fclose(input[1]);
	fclose(output[0]);
	fclose(output[1]);
	
	return 0;
}