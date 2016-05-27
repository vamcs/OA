#include <stdio.h>
#include <stdlib.h>
#include "indices.h"

int main(){
	char file1Name[30], file2Name[30];
	char** txt1;
	char** txt2;
	int totalLines1;
	int totalLines2;
	
	/**************** Lista1.txt **************/
	printf("Entre com o nome do arquivo 1 de entrada: ");
	scanf("%s", file1Name);
	
	totalLines1 = 0;
	txt1 = createText(file1Name, &totalLines1);
	
	Link l1 = secondaryIndexes(txt1, totalLines1);
	
	primaryIndexes(txt1, totalLines1, l1->next);
	
	destroyText(txt1, totalLines1);
	destroyLink(l1->next);
	free(l1);
	l1 = NULL;
	
	/**************** Lista2.txt **************/
	printf("Entre com o nome do arquivo 2 de entrada: ");
	scanf("%s", file2Name);
	
	totalLines2 = 0;
	txt2 = createText(file2Name, &totalLines2);

	Link l2 = secondaryIndexes(txt2, totalLines2);
	
	primaryIndexes(txt2, totalLines2, l2->next);
	
	destroyText(txt2, totalLines2);
	destroyLink(l2->next);
	free(l2);
	l2 = NULL;
	
	return 0;
}