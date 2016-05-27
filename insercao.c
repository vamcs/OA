#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

/*Adiciona espacos em branco entre os campos de nome e op*/
void adicionaEspacos(char* registro) {
	/*49 é a posicao do primeiro caracter do campo op*/
	while (strlen(registro) < 48) {
		strcat(registro, " ");
	}
}

void excluindo(char* chavePrimaria) {

}

/*Concatena as strings de cada campo e mantem a formatacao do arquivo*/
char* formatando(FILE* fp, char* matricula, char* nome, char* op, char* curso, char* turma) {
	char registro[62];
<<<<<<< HEAD
	strcpy(registro, matricula);
=======
	printf("op: %s\n", op);
	strcat(registro, matricula);
>>>>>>> 871dceae874300d0a4d17aa3ef50116075dc873d
	strcat(registro, " ");
	strcat(registro, nome);
	adicionaEspacos(registro);
	strcat(registro, op);
	strcat(registro, "  ");
	strcat(registro, curso);
<<<<<<< HEAD
	strcat(registro, "       ");
	registro[61] = turma;
	registro[62] = '\0';
	printf("%s", registro);
	fprintf(fp, "%s\n", registro);
=======
	strcat(registro, " ");
	strcat(registro, turma);
	printf("registro: %s\n", registro);
>>>>>>> 871dceae874300d0a4d17aa3ef50116075dc873d

	return registro;
}

int main() {
	char nomeDoArquivo[30];
	char escolha = 'z';
	FILE *fp = NULL;

	char *matricula = (char*)malloc(6 * sizeof(char));
	char nome[40];
	char *op = (char*)malloc(2 * sizeof(char));
	char curso[2];
	char turma[1];
	char *registro = (char*)malloc(62 * sizeof(char));

<<<<<<< HEAD
	printf("Informe o nome do arquivo de registros que deseja manipular\n");
	scanf("%[^\n]s", nomeDoArquivo);
	fp = fopen(nomeDoArquivo, "a");

	printf("Deseja fazer insercao (i/I) ou remocao(r/R) ?\n");
	scanf(" %c", &escolha);
	getchar();

	if (escolha == 'i' || escolha == 'I') {
		printf("Qual a matricula ?\n");
		scanf(" %6[^\n]s", matricula);
		getchar();
		//fgets(matricula, 6, stdin);
		printf("Qual o nome ?\n");
		scanf(" %40[^\n]s", nome);
		getchar();
		//fgets(nome, 40, stdin);
		printf("Qual a op ?\n");
		scanf(" %2[^\n]s", op);
		getchar();
		//fgets(op, 2, stdin);
		printf("Qual o curso\n");
		scanf(" %2[^\n]s", curso);
		getchar();
		//fgets(curso, 2, stdin);
		printf("Qual a turma\n");
		scanf(" %c", &turma);

		formatando(fp, matricula, nome, op, curso, turma);
=======
	/*
	fp = fopen(nomeDoArquivo, "r+");
	while(fp == NULL) {
		printf("Informe o nome do arquivo de registros que deseja manipular\n");
		scanf("%s", nomeDoArquivo);
		fp = fopen(nomeDoArquivo, "r+");
	}
	*/

	while (escolha != 'i' && escolha != 'I' && escolha != 'r' &&
		   escolha != 'R' && escolha != 'a' && escolha != 'A' &&
		   escolha != 'Q' && escolha != 'q') {

		printf("Deseja fazer insercao (i/I) ou remocao(r/R) ?\n");
		scanf("%c", &escolha);

		if (escolha == 'Q' || escolha == 'q') {
			break;
		}

		if (escolha == 'i' || escolha == 'I') {
			printf("Qual a matricula ?\n");
			getchar();
			scanf("%s", matricula);
			printf("%s\n", matricula);
			printf("Qual o nome ?\n");
			getchar();
			scanf("%[^\n]s", nome);
			printf("%s\n", nome);
			printf("Qual a op ?\n");
			getchar();
			scanf("%s", op);
			printf("OP: %s\n", op);
			printf("Qual o curso\n");
			getchar();
			scanf("%s", curso);
			printf("Qual a turma\n");
			getchar();
			scanf("%s", turma);

			registro = formatando(fp, matricula, nome, op, curso, turma);

			escolha = 'z';

		}
		else {
			if (escolha == 'r' || escolha == 'R') {
				printf("Digite a chave primaria do registro que deseja excluir, isto e, \n
				a matricula concatenada ao nome sem espacos\n");
				for ()
			}

			if (escolha == 'a' || escolha == 'A') {

			}
		}
		printf("\nSe desejar parar a manipulacao do arquivo digite Q\n");
>>>>>>> 871dceae874300d0a4d17aa3ef50116075dc873d
	}

	fclose(fp);
	return 0;
}