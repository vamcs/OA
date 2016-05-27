#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void troca(char** array, int indice1, int indice2) {
	char *aux;
	printf("\n");
	printf("%d %d\n", indice1, indice2);

	printf("%s\n", array[indice1]);
	printf("%s\n", array[indice2]);
	aux = array[indice1];
	printf("aux	%s\n", aux);
	array[indice1] = array[indice2];
	printf("indice1: %s\n", array[indice1]);
	array[indice2] = aux;
	printf("indice2 %s\n", array[indice2]);
	printf("\n");
}

void buildHeap(char** array, int length) {
	int i, j;
	for (i = 0; i < length; i++) {
		j = i+1;
		printf("j:%dj/2:%d\n", j, j/2);

		while(j > 1 && strcmp(array[j/2], array[j]) < 0) {
			printf("trocou\n");
			troca(array, j/2, j);
			j = j/2;
		}
	}
}

void downHeap(char** array, int length) {
	int j = 1;
	while(j <= length) {
		if (j < length && strcmp(array[j], array[j+1]) < 0) {
			j++;
		}
		if (strcmp(array[j/2], array[j]) >= 0) {
			break;
		}
		troca(array, j/2, j);
		j = j*2;
	}
}


void mHeapsort(char** array, int length) {
	int n;
	printf("length:%d\n", length);
   	buildHeap (array, length);
   for (n = length -1; n >= 2; --n) {
      troca(array, 0, n);
      downHeap(array, n-2);
   }

}

int main () {
	int i, nLinhas = 3;
	char a[] = {"044312LeonardoNunesdeSouza    "};
	char b[] = {"031272AndrezaPollyanadaSilva  "};
	char c[] = {"035830RogerioAugustodeCastro  "};
	char **linhas = (char**)malloc(nLinhas * sizeof(char*));
	linhas[0] = a;
	linhas[1] = b;
	linhas[2] = c;

	printf("Antes da ordenacao\n");
	for (i = 0; i < nLinhas; ++i)
	{
		printf("%s\n", linhas[i]);
	}
	
	mHeapsort(linhas, nLinhas);

	printf("depois da ordencao\n");
	for (i = 0; i < nLinhas; ++i)
	{
		printf("%s\n", linhas[i]);
	}
	return 0;
}