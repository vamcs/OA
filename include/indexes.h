/*Cabeçalho de definições*/

#define X 62  //Número de caracteres por linha das listas

#define bool int
#define true 1
#define false 0

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

/*Funções*/
bool checkCourse(Link, char*);
void insertQueue(Link, char*, int);
Link insertLink(Link, char*, int);
int findNextIndex(Link, char*, int);
void destroyLink(Link);

char** createText(char*, int*);
void saveText(char*, char**, int);
void destroyText(char**, int);

void primaryIndexes(char**, int, Link);
Link secondaryIndexes(char**, int);

void formatando(FILE*, char*, char*, char*, char*, char);
void adicionaEspacos(char*);
void modify();