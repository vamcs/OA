#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>


void adicionaEspacos(char* registro) {
	/*49 é a posicao do primeiro caracter do campo op*/
	while (strlen(registro) < 48) {
		strcat(registro, " ");
	}
}

void formatando(FILE* fp, char* matricula, char* nome, char* op, char* curso, char turma) {
	char registro[62];
	strcat(registro, matricula);
	strcat(registro, " ");
	strcat(registro, nome);
	adicionaEspacos(registro);
	strcat(registro, op);
	strcat(registro, " ");
	strcat(registro, curso);
	strcat(registro, " ");
	int length = strlen(registro);
	registro[length] = turma;
	registro[length +1] = '\0';
	printf("%s\n", registro);

}

int main() {
	char nomeDoArquivo[30];
	char escolha;
	FILE *fp;

	char matricula[6];
	char nome[40];
	char op[2];
	char curso[2];
	char turma;

	fp = fopen(nomeDoArquivo, "r+");
	while(fp == NULL) {
		printf("Informe o nome do arquivo de registros que deseja manipular\n");
		scanf("%s", nomeDoArquivo);
			fp = fopen(nomeDoArquivo, "r+");
	}

	printf("Deseja fazer insercao (i/I) ou remocao(r/R) ?\n");
	scanf("%c", &escolha);
	getchar();

	if (escolha == 'i' || escolha == 'I') {
		printf("Qual a matricula ?\n");
		scanf("%s", matricula);
		printf("Qual o nome ?\n");
		scanf("%s", nome);
		printf("Qual a op ?\n");
		scanf("%s", op);
		printf("Qual o curso\n");
		scanf("%s", curso);
		printf("Qual a turma\n");
		scanf("%c", &turma);

		formatando(fp, matricula, nome, op, curso, turma);
	}

	return 0;
}