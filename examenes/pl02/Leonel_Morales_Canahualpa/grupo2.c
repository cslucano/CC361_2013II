#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n_supresores;
int n_insertores;
sem_t mutex;
sem_t regioncriticaVacia;

typedef struct NodoL{
	char dato;
	struct NodoL* sig;
}Nodo;

typedef struct ListaEnlazada{
	Nodo* inicio;
	Nodo* fin;
	int tamanyo;
}Lista;

void* insercion(Lista* lista);
void* supresion(Lista* lista);
void agregar(Lista* lista, char dato);
void quitar(Lista* lista, int pos);

void agregar(Lista* lista, char dato){
		Nodo* nod = malloc(sizeof(Nodo));
		nod->dato=dato;
		nod->sig=NULL;
		
		if(lista->tamanyo == 0)	lista->inicio = nod;
		lista->fin->sig=nod;
		lista->fin=nod;
		lista->tamanyo++;
		printf("%d\n",lista->tamanyo);
}

void quitar(Lista* lista, int pos){
	if(pos<lista->tamanyo){
		Nodo* bucl=lista->inicio;
		Nodo* bucl_ant;
		if(pos == 0){
			lista->inicio = lista->inicio->sig;
		}else {
			while(pos--){
				bucl_ant=bucl;
				bucl=bucl->sig;
			}
			bucl_ant->sig=bucl->sig;
			if((pos+1) == lista->tamanyo)	lista->fin = bucl_ant;
		}
		free(bucl);
		lista->tamanyo--;
		printf("%d\n",lista->tamanyo);
	}
}

int main(){
	Lista* lista = malloc(sizeof(Lista));
	lista->inicio=NULL;
	lista->fin=NULL;
	lista->tamanyo=0;
	
	n_insertores=0;
	n_supresores=0;
	pthread_t thread_supresor;
	pthread_t thread_insertor;
	pthread_t thread_insertor2;

	sem_init(&mutex,0,1);
	sem_init(&regioncriticaVacia,0,1);

	pthread_create(&thread_supresor, NULL, supresion(lista), NULL );
	printf("ACA\n");
	pthread_create(&thread_insertor, NULL, insercion(lista), NULL );
	pthread_create(&thread_insertor2, NULL, insercion(lista), NULL );

	pthread_join(thread_supresor, NULL);
	return 0;
}

void* insercion(Lista* lista){
	char c;
	int pos;
	while(1){
		sem_wait(&mutex);
			n_insertores++;
			if(n_insertores==1)	sem_wait(&regioncriticaVacia);
		sem_post(&mutex);
			pos = rand()%(lista->tamanyo);
			c = 'a' + rand()%24;
			agregar(lista, c);
		sem_wait(&mutex);
			n_insertores--;
			if(n_insertores==0)	sem_post(&regioncriticaVacia);
		sem_post(&mutex);
		
		sleep(1);

	}
}

void* supresion(Lista* lista){
	int pos;
	while(1){
		sem_wait(&mutex);
			n_supresores++;
			if(n_supresores==1)	sem_wait(&regioncriticaVacia);
		sem_post(&mutex);
			pos = rand()%(lista->tamanyo);
			quitar(lista, pos);
		sem_wait(&mutex);
			n_supresores--;
			if(n_supresores==0)	sem_post(&regioncriticaVacia);
		sem_post(&mutex);
		
		sleep(1);
	}
}
