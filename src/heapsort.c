#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexes.h"

/*Troca a posição das strings com os indices indice1 e indice2*/
void swap(char** a, int indice1, int indice2) {
	char *aux = (char*)malloc(62 * sizeof(char));
	aux = a[indice1];
	a[indice1] = a[indice2];
	a[indice2] = aux;
}
 
/*Compara dois elementos e retorna o maior deles*/
int max (char** a, int n, int i, int j, int k) {
    int m = i;
    if (j < n && strcmp(a[j], a[m]) > 0) {
        m = j;
    }
    if (k < n && strcmp(a[k], a[m]) > 0) {
        m = k;
    }
    return m;
}
/*Troca o filho de maior valor com o pai*/
void downheap (char** a, int n, int i) {
    while (1) {
        int j = max(a, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        swap(a, j, i);
        i = j;
    }
}

/*Funcao de ordenção Heap sort*/
void mHeapsort (char** a, int length) {
    int i;
    /*Construindo a estrutura do heap*/
    for (i = (length - 2) / 2; i >= 0; i--) {
        downheap(a, length, i);
    }
    /*ordenando em ordem crescente o heap*/
    for (i = 0; i < length; i++) {
    	swap(a, length -i -1, 0);
        downheap(a, length - i - 1, 0);
    }
}
 
// int main () {
// 	int i, nLinhas = 3;
// 	char a[30] = {"044312LeonardoNunesdeSouza    "};
// 	char b[30] = {"031272AndrezaPollyanadaSilva  "};
// 	char c[30] = {"035830RogerioAugustodeCastro  "};
// 	char **linhas = (char**)malloc(nLinhas * sizeof(char*));
// 	linhas[0] = a;
// 	linhas[1] = b;
// 	linhas[2] = c;

// 	printf("Antes da ordenacao\n");
// 	for (i = 0; i < nLinhas; ++i)
// 	{
// 		printf("%s\n", linhas[i]);
// 	}
// 	printf("\n");
	
// 	mHeapsort(linhas, nLinhas);

// 	printf("depois da ordencao\n");
// 	for (i = 0; i < nLinhas; ++i)
// 	{
// 		printf("%s\n", linhas[i]);
// 	}
// 	return 0;
// }

