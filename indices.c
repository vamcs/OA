#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

#define X 62  //Número de caracteres por linha das listas
#define Y1 19 //Número inicial de linhas das listas1.txt
#define Y2 22 //Número inicial de linhas das listas2.txt

/*Estrutura da Fila de Próximos Índices Primários*/
/*
Guarda todas as ocorrências de índices que contêm o mesmo
curso do índice inicial contido na lista de cursos.
*/
typedef struct queue *Queue;
struct queue{
	int index;
	Queue next;
};

/*Estrutura da Lista Encadeada de Cursos*/
/*
Esta estrutura contém uma lista encadeada que contém o nome do curso,
o índice de primeira ocorrência de um curso e ponteiros para uma fila 
que contém todos as próximas ocorrências do curso em outros registros.
*/
typedef struct link *Link;
struct link{
	char course[2];
	int index;
	Queue first;
	Queue last;
	Link next;
};

/*
Verifica se o curso lido já existe na lista de cursos.
*/
bool checkCourse(Link list, char* course){
	while(list != NULL){
		if(strcmp(list->course, course) == 0) return true;
		list = list->next;
	}
	return false;
}

/*
Insere um índice primário cujo curso é o mesmo do nó da
lista de cursos à qual a fila pertence. No caso, "list".
Ou seja, identificação de todos próximos registros cujo
curso seja igual ao registro de índice inicial list->index.
*/
void insertQueue(Link list, char* course, int lineNumber){
	
	Queue new = (Queue)malloc(sizeof(*new));
	
	//Encontra o nó da lista de cursos correspondente.
	while(strcmp(list->course, course) != 0 && list != NULL) list = list->next;
	
	if(list != NULL && list->first != NULL){		//Caso ainda não exista uma fila, cria uma.
		new->index = lineNumber;
		new->next = NULL;
		list->last->next = new;
		list->last = new;
	}
	else if(list != NULL && list->first == NULL){	//Caso contrário, adiciona o novo nó ao final da fila.
		new->index = lineNumber;
		new->next = NULL;
		list->first = new;
		list->last = new;
	}
}

/*
Insere um novo nó na lista encadeada, o que representa um novo curso
lido no arquivo lista1.txt / lista2.txt. Os nós são inseridos no início
da lista.
*/
Link insertLink(Link list, char* course, int lineNumber){
	
	Link new = (Link)malloc(sizeof(*new));
	
	strcpy(new->course, course);
	
	new->index = lineNumber;
	new->first = NULL;
	new->last = NULL;
	new->next = list;
	
	return new;
}

/*Retorna o índice existente na estrutura dos índices secundários.*/
int findNextIndex(Link list, char* course, int index){
	Queue aux;
	while(list != NULL && strcmp(list->course, course) != 0) list = list->next;		//Busca pelo curso na lista de cursos.
	if(list->index == index && list->first != NULL) 	//É o nó da lista e possui próximos índices.
		return list->first->index;		//É o próprio nó da lista.
	else if(list->first == NULL)		//Nó da lista de cursos não possui próximos índices.
		return -1;
	else{								//Procura na fila de próximos do nó da lista.
		for(aux = list->first; aux != NULL && aux->index != index; aux = aux->next);
		if(aux->next == NULL) 
			return -1;
		else 
			return aux->next->index;
	}
}

/*
 * Desalocação da Memória da Lista de Cursos.
 */
void destroy(Link list){
	Link aux;
	Queue aux2;
	while(list != NULL){
		aux = list->next;
		while(list->first != NULL){
			aux2 = list->first->next;
			free(list->first);
			list->first = NULL;
			list->first = aux2;
		}
		free(list);
		list = aux;
	}
	list = NULL;
}

void destroyText(char** txt, int totalLines){
	for(int i = 0; i < totalLines; i++){
		free(txt[i]);
	}
	//free(txt);
}

char** createTxt(char* fileName, int* totalLines){
	char aux;		//Variável auxiliar de leitura. Lê '\n' e garante a mudança de linha do ponteiro do arquivo.
	
	/*Inicialização do Arquivo de Entrada*/
	FILE* input = fopen(fileName, "r");
	while(input == NULL){
		printf("Arquivo %s inexistente. Entre com o nome correto.\n", fileName);
		scanf("%s", fileName);
		input = fopen(fileName, "r");
	}
	
	/*Contagem do número de linhas do arquivo de entrada.*/
	while(!feof(input)){
		aux = fgetc(input);
		if(aux == '\n'){
			*totalLines = *totalLines + 1;
		}
	}
	
	/*Volta o ponteiro ao início do arquivo de entrada.*/
	rewind(input);
	
	char** txt = (char**)malloc(*totalLines * sizeof(char*));
	for(int lineNumber = 0; lineNumber < *totalLines; lineNumber++){
		txt[lineNumber] = (char*)malloc(X * sizeof(char));	//As linhas possuem X (constante) caracteres.
		fscanf(input, "%[^\n]s", txt[lineNumber]);		//Lê uma linha completa.
		fscanf(input, "%c", &aux);			//Lê '\n'
	}
	
	fclose(input);
	return txt;
}

/*FUNÇÃO AINDA INCOMPLETA.
 *Entretanto, já imprime os índices primários.
 */
void primaryIndexes(char** txt, int totalLines, Link list){
	int i = 0;		//Variável de navegação da string que contém uma linha inteira do arquivo de entrada.
	int j = 0;		//Variável de navegação da string da chave primária.
	int next;		//Armazena o próximo índice para o registro com a mesma chave secundária.
	int flag = 0;	//Flag indica se um espaço ' ' foi lido duas vezes seguidas.
	int lineNumber;	//Esta variável indica o número da linha atual lida nos arquivos lista1.txt ou lista2.txt.
	char primaryKey[30];	//String que contém a CHAVE PRIMÁRIA concatenada com 30 caracteres.
	char course[2];	//Armazena o curso lido por line nas posições 52 e 53.
	char outputName[20];	//String do nome do arquivo de saída output.
	
	
	/*Inicialização dos Arquivos de Saída*/
	printf("Entre com o nome do arquivo de saida dos indices primarios da mesma lista: ");
	scanf("%s", outputName);
	FILE* output = fopen(outputName, "w");
	
	//Criação do Arquivo de Índices Primários do Arquivo lista1.txt
	for(lineNumber = 0;  lineNumber < totalLines; lineNumber++){	//Lê as Y1 linhas do arquivo lista1.txt
		while(j < 30 && i < X && flag < 2){					//Concatenação de 30 primeiros caracteres diferentes de ' '.
			if(txt[lineNumber][i] != ' '){					//Continua a concatenação enquanto j < 30, i < X e flag não indica leitura de dois espaços seguidos.
				primaryKey[j] = txt[lineNumber][i];			//Copia caractere da linha para a chave primária
				i++;										//Incrementa o navegador da linha.
				j++;										//Incrementa o navegador da chave primária.
				flag = 0;									//Seta a flag em 0, já que não foram detectados dois ' ' seguidos.
			}
			else{
				i++;										//Incrementa o navegador da linha.
				flag++;										//Detectado 1 espaço, incrementa.
			}
		}
		while(j < 30){										//Caso a string da chave não tenha 30 caracteres, completa com espaços.
			primaryKey[j] = ' ';
			j++;
		}
		primaryKey[30] = '\0';								//Caractere de final da string.
		
		course[0] = txt[lineNumber][52];					//Curso está nas posições 52 e 53. '\0' termina a string.
		course[1] = txt[lineNumber][53];
		course[2] = '\0';
		
		next = findNextIndex(list, course, lineNumber);
		
		fprintf(output, "%d\t%s\t%d\t%d\n", lineNumber, primaryKey, lineNumber, next);	//Imprime: "índicePrimário chavePrimária NRR" no arquivo de saída.
		i = 0;												//Reinicia variáveis de navegação e flag.
		j = 0;
		flag = 0;
	}
	
	fclose(output);
}

/*FUNÇÃO AINDA INCOMPLETA.
 *A criação da estrutura de índices secundário funciona, mas só os imprime na tela.
 *TODO: Estender a criação dos índices para o arquivo lista2.txt e imprimir nos arquivos de saída.
 *      Verificar integração com "primaryIndexes".
 */
Link secondaryIndexes(char** txt, int totalLines){
	Link aux;
	char course[2];
	int lineNumber;
	char outputName[20];
	
	/*Inicialização do Arquivo de Saída*/
	printf("Entre com o nome do arquivo de saida dos indices secundarios: ");
	scanf("%s", outputName);
	FILE* output = fopen(outputName, "w");
	
	/*Inicialização da Lista Encadeada de Cursos*/
	/*Criação da cabeça da lista.*/
	Link coursesList = (Link)malloc(sizeof(*coursesList));
	coursesList->index = -1;
	coursesList->next = NULL;
	coursesList->first = NULL;
	coursesList->last = NULL;

	for(lineNumber = 0; lineNumber < totalLines; lineNumber++){
		
		//As posições 52 e 53 contêm a string do curso.
		course[0] = txt[lineNumber][52];
		course[1] = txt[lineNumber][53];
		course[2] = '\0';
		
		if(checkCourse(coursesList->next, course)){	//Verifica se o curso lido já existe na lista de cursos.
			//Caso positivo, procura o nó que contém o curso desejado e coloca o índice primário na fila.
			insertQueue(coursesList->next, course, lineNumber);
		}
		else{	//Caso o curso não exista na lista, cria-se um novo nó contendo o curso lido, incluindo o primeiro índice de ocorrência do curso no arquivo.
			coursesList->next = insertLink(coursesList->next, course, lineNumber);
		}
	}
	
	/*Impressão da Lista de Cursos e da fila de ponteiros na tela*/
	//Percorre toda a lista de cursos e suas respectivas filas de próximos índices primários.
	/*Link aux2;
	Queue aux3;
	for(aux2 = coursesList->next; aux2 != NULL; aux2 = aux2->next){
		printf("%s: %d\n", aux2->course, aux2->index);
		for(aux3 = aux2->first; aux3 != NULL; aux3 = aux3->next){
			printf("%d ", aux3->index);
		}
		printf("\n");
	}*/

	aux = coursesList->next;
	while(aux != NULL){
		fprintf(output, "%s:\t%d\n", aux->course, aux->index);
		aux = aux->next;
	}

	fclose(output);
	return coursesList;
}


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
	txt1 = createTxt(file1Name, &totalLines1);
	
	Link l1 = secondaryIndexes(txt1, totalLines1);
	
	primaryIndexes(txt1, totalLines1, l1->next);
	
	destroyText(txt1, totalLines1);
	destroy(l1->next);
	free(l1);
	l1 = NULL;
	
	/**************** Lista2.txt **************/
	printf("Entre com o nome do arquivo 2 de entrada: ");
	scanf("%s", file2Name);
	
	totalLines2 = 0;
	txt2 = createTxt(file2Name, &totalLines2);

	Link l2 = secondaryIndexes(txt2, totalLines2);
	
	primaryIndexes(txt2, totalLines2, l2->next);
	
	destroyText(txt2, totalLines2);
	destroy(l2->next);
	free(l2);
	l2 = NULL;
	
	return 0;
}