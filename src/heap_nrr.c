#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indexes.h"

/*Troca a posição das strings com os indices indice1 e indice2*/
void nrrswap(NRR a, int indice1, int indice2) {
	NRR aux = (NRR)malloc(sizeof(struct nrr));
	
	strcpy(aux[0].matricula, a[indice1].matricula);
	aux[0].NRR = a[indice1].NRR;

	strcpy(a[indice1].matricula, a[indice2].matricula);
	a[indice1].NRR = a[indice2].NRR;

	strcpy(a[indice2].matricula, aux[0].matricula);
	a[indice2].NRR = aux[0].NRR;

	free(aux);
}
 
/*Compara dois elementos e retorna o maior deles*/
int nrrmax (NRR a, int n, int i, int j, int k) {
    int m = i;
    if (j < n && strcmp(a[j].matricula, a[m].matricula) > 0) {
        m = j;
    }
    if (k < n && strcmp(a[k].matricula, a[m].matricula) > 0) {
        m = k;
    }
    return m;
}
/*Troca o filho de maior valor com o pai*/
void nrrdownheap (NRR a, int n, int i) {
    while (1) {
        int j = nrrmax(a, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        nrrswap(a, j, i);
        i = j;
    }
}

/*Funcao de ordenção Heap sort*/
void nrrHeapsort (NRR a, int length) {
    int i;
    /*Construindo a estrutura do heap*/
    for (i = (length - 2) / 2; i >= 0; i--) {
        nrrdownheap(a, length, i);
    }
    /*ordenando em ordem crescente o heap*/
    for (i = 0; i < length; i++) {
    	nrrswap(a, length -i -1, 0);
        nrrdownheap(a, length - i - 1, 0);
    }
}
 
// int main () {
// 	int i, nLinhas = 3;
// 	char a[6] = {"044312"};
// 	char b[6] = {"031272"};
// 	char c[6] = {"035830"};
// 	NRR linhas = (NRR)malloc(nLinhas * sizeof(struct nrr));

// 	strcpy(linhas[0].matricula, a);
// 	linhas[0].NRR = 0;
// 	strcpy(linhas[1].matricula, b);
// 	linhas[1].NRR = 1;
// 	strcpy(linhas[2].matricula, c);
// 	linhas[2].NRR = 2;


// 	printf("Antes da ordenacao\n");
// 	for (i = 0; i < nLinhas; ++i)
// 	{
// 		printf("%s - %d\n", linhas[i].matricula, linhas[i].NRR);
// 	}
// 	printf("\n");
	
// 	mHeapsort(linhas, nLinhas);

// 	printf("depois da ordencao\n");
// 	for (i = 0; i < nLinhas; ++i)
// 	{
// 		printf("%s - %d\n", linhas[i].matricula, linhas[i].NRR);
// 	}
// 	return 0;

// 	free(linhas);
// }

