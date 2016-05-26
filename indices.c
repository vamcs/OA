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

/*FUNÇÃO AINDA INCOMPLETA.
 *Entretanto, já imprime os índices primários.
 */
void primaryIndexes(){
	int i = 0;		//Variável de navegação da string que contém uma linha inteira do arquivo de entrada.
	int j = 0;		//Variável de navegação da string da chave primária.
	int flag = 0;	//Flag indica se um espaço ' ' foi lido duas vezes seguidas.
	int lineNumber;	//Esta variável indica o número da linha atual lida nos arquivos lista1.txt ou lista2.txt.
	char aux;		//Variável auxiliar de leitura. Lê '\n' e garante a mudança de linha do ponteiro do arquivo.
	char index[30];	//String que contém a CHAVE PRIMÁRIA concatenada com 30 caracteres.
	char line[X];	//String que lê uma linha inteira do arquivo de entrada. Cada linha contem X (62) caracteres.
	
	/*Inicialização dos Arquivos de Entrada*/
	FILE* input[2];
	input[0] = fopen("lista1.txt", "r");
	input[1] = fopen("lista2.txt", "r");
	if(input[0] == NULL || input[0] == NULL){
		printf("Arquivos inexistentes. Stop.\n");
		exit(1);
	}
	
	/*Inicialização dos Arquivos de Saída*/
	FILE* output[2];
	output[0] = fopen("indicelista1.ind", "w"); 
	output[1] = fopen("indicelista2.ind", "w"); 
	
	for(lineNumber = 0;  lineNumber < Y1; lineNumber++){	//Lê as Y1 linhas do arquivo lista1.txt
		fscanf(input[0], "%[^\n]s", line);					//Leitura da primeira linha.
		fscanf(input[0], "%c", &aux);						//Leitura de '\n'.
		while(j < 30 && i < X && flag < 2){					//Concatenação de 30 primeiros caracteres diferentes de ' '.
			if(line[i] != ' '){								//Continua a concatenação enquanto j < 30, i < X e flag não indica leitura de dois espaços seguidos.
				index[j] = line[i];							//Copia caractere da linha para a chave primária
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
			index[j] = ' ';
			j++;
		}
		index[30] = '\0';									//Caractere de final da string.
		
		fprintf(output[0], "%s %d\n", index, lineNumber);	//Imprime: "chavePrimária NRR" no arquivo de saída.
		i = 0;												//Reinicia variáveis de navegação e flag.
		j = 0;
		flag = 0;
	}
	
	//O procedimento é exatamente o mesmo do arquivo de entrada 1 (lista1.txt).
	for(lineNumber = 0; lineNumber < Y2; lineNumber++){
		fscanf(input[1], "%[^\n]s", line);
		fscanf(input[1], "%c", &aux);
		while(j < 30 && i < X && flag < 2){
			if(line[i] != ' '){
				index[j] = line[i];
				i++;
				j++;
				flag = 0;
			}
			else{
				i++;
				flag++;
			}
		}
		
		while(j < 30){
			index[j] = ' ';
			j++;
		}
		
		index[30] = '\0';
		
		fprintf(output[1], "%s %d\n", index, lineNumber);
		i = 0;
		j = 0;
		flag = 0;
	}
	
	fclose(input[0]);
	fclose(input[1]);
	fclose(output[0]);
	fclose(output[1]);
}

/*FUNÇÃO AINDA INCOMPLETA.
 *A criação da estrutura de índices secundário funciona, mas só os imprime na tela.
 *TODO: Estender a criação dos índices para o arquivo lista2.txt e imprimir nos arquivos de saída.
 *      Verificar integração com "primaryIndexes".
 */
Link secondaryIndexes(){
	char line[X];
	char aux;
	char course[2];
	int lineNumber;
	
	/*Inicialização da Lista Encadeada de Cursos*/
	Link coursesList = (Link)malloc(sizeof(*coursesList));
	coursesList->next = NULL;
	coursesList->first = NULL;
	coursesList->last = NULL;
	
	/*Inicialização dos Arquivos de Entrada*/
	FILE* input[2];
	input[0] = fopen("lista1.txt", "r");
	input[1] = fopen("lista2.txt", "r");
	if(input[0] == NULL || input[0] == NULL){
		printf("Arquivos inexistentes. Stop.\n");
		exit(1);
	}
	
	/*Inicialização dos Arquivos de Saída*/
	FILE* output[2];
	output[0] = fopen("indiceSecundariolista1.ind", "w"); 
	output[1] = fopen("indiceSecundariolista2.ind", "w"); 
	
	//Leitura de todas as linhas do arquivo de entrada 1 (input[0]).
	for(lineNumber = 0; lineNumber < Y1; lineNumber++){
		fscanf(input[0], "%[^\n]s", line);		//Lê uma linha completa.
		fscanf(input[0], "%c", &aux);			//Lê '\n'
		
		//As posições 52 e 53 contêm a string do curso.
		course[0] = line[52];
		course[1] = line[53];
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
	Link aux2;
	Queue aux3;
	for(aux2 = coursesList->next; aux2 != NULL; aux2 = aux2->next){
		printf("%s: %d\n", aux2->course, aux2->index);
		for(aux3 = aux2->first; aux3 != NULL; aux3 = aux3->next){
			printf("%d ", aux3->index);
		}
		printf("\n");
	}
	
	fclose(input[0]);
	fclose(input[1]);
	fclose(output[0]);
	fclose(output[1]);
	return coursesList;
}

/*Salva um arquivo de índices secundários.*/
void outputFile(Link list, FILE* output){
	while(list != NULL){
		fprintf(output, "%s: %d\n", list->course, list->index);
		list = list->next;
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
			list->first = aux2;
		}
		free(list);
		list = aux;
	}
}


int main(){
	
	Link l = secondaryIndexes();
	
	destroy(l);
	
	return 0;
}