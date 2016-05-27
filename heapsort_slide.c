#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heapify (char* array, int p) {
	int L = 2*p;
	int R = 2*p + 1;
	int maior;
	/*30 pois esse é o maior tamanho das strings que irão ser ordenadas*/
	char aux[30];

	if (L != NULL && strcmp(array[L], array[R]) > 0)
		maior = L;
	else maior = p;

	if (maior != p) {
		/*trocando*/
		aux = array[p];
		array[p] = array[maior];
		array[maior] = aux;

		heapify(array, maior);
	}

}


void buildHeap(char* array, int length) {
	for (int p = length	/2; p >= 1; p--) {
		heapify(array, p);

	}
}

void heapsort(char* array, int length) {
	buildHeap(a, length);
	char aux[30];
	for (int p = length; p >= 2; p--) {
		aux = array[0];
		array[0] = array[p];
		array[p] = aux;

		length--;

		heapify(array, 0)

	}

}

int main () {
	int nLinhas = 2;
	int length = ;
	char a[] = {"024312LeonardoNunesdeSouza    "};
	char b[] = {"031272AndrezaPollyanadaSilva  "};
	char **linhas = (char**)malloc(nLinhas * sizeof(char*));
	linhas[0] = a;
	linhas[1] = b;

	heapsort(a, length);

	return 0;
}