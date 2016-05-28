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

/*Estrutura para guardar o NRR original*/
typedef struct nrr *NRR;
struct nrr{
	char matricula[6];
	int NRR;
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

void primaryIndexes(char**, int, Link, NRR, char*);
Link secondaryIndexes(char**, int, char*);

void formatando(FILE*, char*, char*, char*, char*, char);
void adicionaEspacos(char*);
void modify(char*);

void merge();
void escreveNoArquivo(FILE*, char*);
void lerLista(FILE*, char*);

void mHeapsort (char**, int);
void downheap (char**, int, int);
int max (char**, int, int, int, int);
void swap(char**, int, int);

void nrrHeapsort (NRR, int);
void nrrdownheap (NRR, int, int);
int nrrmax (NRR, int, int, int, int);
void nrrswap(NRR, int, int);