#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void troca(char** array, int indice1, int indice2) {
	char aux[30];
	strcpy(aux, array[indice1]);
	strcpy(array[indice1], array[indice2]);
	strcpy(array[indice2], aux);
}

void heapify (char** array, int p) {
	p--;
	char *L = array[2*p];
	char *R = array[2*p +1];
	int maior;
	printf("p:%d\n", p);
	
	if (L != NULL && strcmp(L, R) > 0) {
		printf("KK\n");
				maior = 2*p;
	}
	else {
		printf("GG\n");
		maior = p;
	}

	if (R != NULL && strcmp(R, array[maior])) {

		maior = 2*p + 1;
	}

	if (maior != p) {
		troca(array, p , maior);

		heapify(array, maior);
	}

}


void buildHeap(char** array, int length) {
	for (int p = length	/2; p >= 0; p--) {
		heapify(array, p);

	}
}

void mHeapsort(char** array, int length) {
	buildHeap(array, length);
	printf("OI\n");
	for (int p = length; p >= 2; p--) {
		troca(array, 0, p);

		length--;

		heapify(array, 0);
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