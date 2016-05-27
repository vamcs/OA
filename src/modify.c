#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "indexes.h"

void adicionaEspacos(char* registro) {
	/*49 é a posicao do primeiro caracter do campo op*/
	while (strlen(registro) < 48) {
		strcat(registro, " ");
	}
}

void formatando(char* registro, char* matricula, char* nome, char* op, char* curso, char turma) {
	strcpy(registro, matricula);
	strcat(registro, " ");
	strcat(registro, nome);
	adicionaEspacos(registro);
	strcat(registro, op);
	strcat(registro, "  ");
	strcat(registro, curso);
	strcat(registro, "       ");
	registro[61] = turma;
	registro[62] = '\0';
}

void modify(char** txt, int* totalLines, char* fileName) {
	char escolha;

	printf("Deseja fazer inserção (i/I), remoção (r/R) ou alteração (a/A)?\n");
	scanf(" %c", &escolha);
	getchar();

	//printf("Informe o nome do arquivo de registros que deseja manipular\n");
	//scanf("%[^\n]s", nomeDoArquivo);

	if (escolha == 'i' || escolha == 'I') {

		char matricula[6];
		char nome[40];
		char op[2];
		char curso[2];
		char turma;
		char novo_registro[62];
		//FILE *fp;

		//fp = fopen(nomeDoArquivo, "a");

		printf("Qual a matricula ?\n");
		scanf(" %6[^\n]s", matricula);
		getchar();
		
		printf("Qual o nome ?\n");
		scanf(" %40[^\n]s", nome);
		getchar();
		
		printf("Qual a op ?\n");
		scanf(" %2[^\n]s", op);
		getchar();
		
		printf("Qual o curso\n");
		scanf(" %2[^\n]s", curso);
		getchar();
		
		printf("Qual a turma\n");
		scanf(" %c", &turma);

		formatando(novo_registro, matricula, nome, op, curso, turma);

		*totalLines = *totalLines + 1;

		char** ptr = (char**)realloc(txt, *totalLines * sizeof(char*));
		if(ptr != NULL){
			txt = ptr;
		}
		txt[*totalLines - 1] = (char*)calloc(1, X * sizeof(char) + 1);

		strcpy(txt[*totalLines - 1], novo_registro);
	}

	else if(escolha == 'r' || escolha == 'R') {
		char** txt;
		char* temp;
		int NRR, option, i;

		printf("Qual linha deve ser deletada?\n");
		scanf("%d", &NRR);
		while(NRR > *totalLines) {
			printf("Número além do limite. Máximo %d linhas. Entre com um novo valor.\n", *totalLines);
			scanf("%d", &NRR);
		}

		NRR--;
		temp = txt[NRR];
		
		if(NRR == *totalLines-1) {		//Remoção do último registro
			*totalLines = *totalLines - 1;
			txt = (char**)realloc(txt, *totalLines * sizeof(char*));
		}
		else {						//Remoção de qualquer outro acima.
			for(i = NRR; i < *totalLines-1; i++){
				txt[i] = txt[i+1];
			}
			free(temp);
			*totalLines = *totalLines - 1;
			txt = (char**)realloc(txt, *totalLines * sizeof(char*));
		}

		saveText(fileName, txt, *totalLines);
	}

	else if(escolha == 'a' || escolha == 'A') {
		char** txt;
		int NRR, i, option;
		char matricula[6];
		char nome[40];
		char op[2];
		char curso[2];
		char turma;

		printf("Qual linha deve ser alterada?\n");
		scanf("%d", &NRR);
		while(NRR > *totalLines) {
			printf("Número além do limite. Máximo %d linhas. Entre com um novo valor.\n", *totalLines);
			scanf("%d", &NRR);
		}
		NRR--;
		printf("%s\n", txt[NRR]);
		printf("Alterar matrícula, nome, OP, curso ou turma?\n");
		printf("Matrícula: 1\tNome: 2\tOP: 3\tCurso: 4\tTurma: 5\n");

		scanf("%d", &option);
		switch(option){
			case 1:
				printf("Entre com a nova matrícula: ");
				scanf(" %6[^\n]s", matricula);
				getchar();
				for(i = 0; i < 6; i++) txt[NRR][i] = matricula[i];
				break;
			case 2:
				printf("Entre com o novo nome: ");
				scanf(" %40[^\n]s", nome);
				getchar();
				for(i = 7; i < strlen(nome); i++) txt[NRR][i] = nome[i];
				if(strlen(nome) < 40){
					while(i < 47){
						txt[NRR][i] = ' ';
					}
				}
				break;
			case 3:
				printf("Entre com o novo OP: ");
				scanf(" %2[^\n]s", op);
				getchar();
				txt[NRR][48] = op[0];
				txt[NRR][49] = op[1];
				break;
			case 4:
				printf("Entre com o novo curso: ");
				scanf(" %2[^\n]s", curso);
				getchar();
				txt[NRR][52] = curso[0];
				txt[NRR][53] = curso[1];
				break;
			case 5:
				printf("Entre com a nova turma: ");
				scanf(" %c", &turma);
				getchar();
				txt[NRR][61] = turma;
				break;
			default:
				break;
		}

		saveText(fileName, txt, *totalLines);
	}
}