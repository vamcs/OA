#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>

static bool acabou1delas = false;
static bool existeRegistro = true;

static void changeShared(void)
{
	existeRegistro = false;
}


void lerLista(FILE *fp, char* registro) {
	char *string_MAX = {"ZZZ"};
	if ( fscanf(fp, "%[^\n]s", registro) != EOF) {
		fgetc(fp);
	}
	else {
		/*Com isso garantimos que quando for feita a comparacao entre esta
		 *chave e a chave do outro arquivo a outra sempre será menor*/
		strcpy(registro, string_MAX);
		if (acabou1delas) {
			changeShared();
			printf("Naoexiste\n");
		}
		printf("uma acabou\n");
		acabou1delas = true;
	}
}

void escreveNoArquivo(FILE* fp, char *registro) {
	fprintf(fp, "%s\n", registro);
}

int main() {
	int i = 0;
	bool existeRegistro = true;
	FILE *lista1 = fopen("lista1.txt", "r");
	FILE *lista2 = fopen("lista2.txt", "r");
	FILE *lista12 = fopen("lista12.txt", "w");
	char *registro1 = (char*)malloc(62 * sizeof(char));
	char *registro2 = (char*)malloc(62 * sizeof(char));
	/*lendo os primeiros registros*/
	lerLista(lista1, registro1);
	lerLista(lista2, registro2);

	while(existeRegistro && i < 10) {

		if (strcmp(registro1, registro2) < 0) {
			/*caso positivo, significa que a chave do registro da lista 1 é menor*/
			escreveNoArquivo(lista12, registro1);
			printf("%s\n", registro1);
			lerLista(lista1, registro1);
		}
		else {
			/*caso a chave do registro da lista 2 seja menor*/
			if (strcmp(registro1, registro2) > 0) {
				printf("%s\n", registro2);
				escreveNoArquivo(lista12, registro2);
				lerLista(lista2, registro2);
			}
			/*caso os dois registros sejam iguais*/
			else {
				escreveNoArquivo(lista12, registro1);
							printf("%s\n", registro1);
				lerLista(lista1, registro1);
				lerLista(lista2, registro2);
			}
		}
		if (existeRegistro) {
			printf("S\n");
		}
		else {
			printf("N\n");
		}
		i++;
	}
	fclose(lista1);
	fclose(lista2);
	fclose(lista12);
	free(registro1);
	free(registro2);
	return 0;
}