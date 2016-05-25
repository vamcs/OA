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
	int i = 0;		//Variável de navegação da string que contém uma linha inteira do arquivo de entrada.
	int j = 0;		//Variável de navegação da string da chave primária.
	int flag = 0;	//Flag indica se um espaço ' ' foi lido duas vezes seguidas.
	int lineNumber;	//Esta variável indica o número da linha atual lida nos arquivos lista1.txt ou lista2.txt.
	char aux;		//Variável auxiliar de leitura. Lê '\n' e garante a mudança de linha do ponteiro do arquivo.
	char index[30];	//String que contém a CHAVE PRIMÁRIA concatenada com 30 caracteres.
	char line[X];	//String que lê uma linha inteira do arquivo de entrada. Cada linha contem X (62) caracteres.
	
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
	
	for(lineNumber = 0;  lineNumber < Y1; lineNumber++){	//Lê as Y1 linhas do arquivo lista1.txt
		fscanf(input[0], "%[^\n]s", line);					//Leitura da primeira linha.
		fscanf(input[0], "%c", &aux);						//Leitura de '\n'.
		while(j < 30 && i < X && flag < 2){					//Concatenação de 30 primeiros caracteres diferentes de ' '.
			if(line[i] != ' '){								//Continua a concatenação enquanto j < 30, i < X e flag não indica leitura de dois espaços seguidos.
				index[j] = line[i];							//Copia caractere da linha para a chave primária
				i++;										//Incrementa o navegador da linha.
				j++;										//Incrementa o navegador da chave primária.
				flag = 0;									//Seta a flag em 0, já que não foram detectados dois ' ' seguidos.
			}
			else{
				i++;										//Incrementa o navegador da linha.
				flag++;										//Detectado 1 espaço, incrementa.
			}
		}
		
		while(j < 30){										//Caso a string da chave não tenha 30 caracteres, completa com espaços.
			index[j] = ' ';
			j++;
		}
		index[30] = '\0';									//Caractere de final da string.
		
		fprintf(output[0], "%s %d\n", index, lineNumber);	//Imprime: "chavePrimária NRR" no arquivo de saída.
		i = 0;												//Reinicia variáveis de navegação e flag.
		j = 0;
		flag = 0;
	}
	
	//O procedimento é exatamente o mesmo do arquivo de entrada 1 (lista1.txt).
	for(lineNumber = 0;  lineNumber < Y2; lineNumber++){
		fscanf(input[1], "%[^\n]s", line);
		fscanf(input[1], "%c", &aux);
		while(j < 30 && i < X && flag < 2){
			if(line[i] != ' '){
				index[j] = line[i];
				i++;
				j++;
				flag = 0;
			}
			else{
				i++;
				flag++;
			}
		}
		
		while(j < 30){
			index[j] = ' ';
			j++;
		}
		
		index[30] = '\0';
		
		fprintf(output[1], "%s %d\n", index, lineNumber);
		i = 0;
		j = 0;
		flag = 0;
	}
	
	fclose(input[0]);
	fclose(input[1]);
	fclose(output[0]);
	fclose(output[1]);
	
	return 0;
}