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
	printf("%s", registro);
	fprintf(fp, "%s\n", registro);

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
	}

	fclose(fp);
	return 0;
}