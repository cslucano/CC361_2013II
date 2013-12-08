#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct Nodo{
	struct Nodo *siguiente;
	struct Nodo *anterior;
	char valor;
}Elemento;

typedef struct ListaEnlazada {
	int tamano;
	Elemento *inicio;
	Elemento *fin;
	
}Lista;

Lista *list;

//Funciones
int insercion(Lista *lista, char dato);
int supresion(Lista *lista, int pos);
void *consumidor(void *arg);
void *productor(void *arg);


//Creo las variables semaforo
sem_t nodosUsados;
sem_t nodosVacios;

//Creo variable mutex
pthread_mutex_t mymutex;


int main() {
	//inicializo los semaforos
	sem_init(&nodosUsados, 0, 0);
	sem_init(&nodosVacios, 0, 100);

	//mutex
	pthread_mutex_init(&mymutex, NULL);
	
	//Creo variables tid threads
	pthread_t thread_productor;
	pthread_t thread_consumidor;

	//inicializar lista
	
	list->inicio = NULL;
	list->fin = NULL;

	//creo los threads
	pthread_create(&thread_productor, NULL, productor, NULL);
	pthread_create(&thread_consumidor, NULL, consumidor, NULL);

	//espero a que finalice los threads
	pthread_join(thread_productor, NULL);
	pthread_join(thread_consumidor, NULL);

	//termino el main
	pthread_exit(NULL);


}
int insercion(Lista *lista, char dato) { //int es para los indices
	pthread_mutex_lock(&mymutex);
	Elemento *nuevo = malloc(sizeof(Elemento));
	
	nuevo->valor = dato;
	sem_wait(&nodosVacios);
	if(lista->inicio == NULL)
		nuevo->siguiente = NULL;
		nuevo->anterior = NULL;
		lista->inicio = nuevo;
		lista->fin = nuevo;
		
	lista->fin = nuevo;
	nuevo->anterior = NULL;
	nuevo->siguiente = lista->fin->siguiente; 

	lista->tamano += 1;
	printf("Nodo : %c", nuevo->valor);
	sem_post(&nodosUsados);	
	pthread_mutex_unlock(&mymutex);
	 
	return lista->tamano;		
}

int supresion(Lista *lista, int pos) {
	pthread_mutex_lock(&mymutex);
	sem_wait(&nodosUsados);
	Elemento *temp = lista->fin;
	lista->fin->siguiente = lista->fin;
	lista->tamano -= 1; 
	free(temp);
	
	sem_wait(&nodosVacios);
	pthread_mutex_unlock(&mymutex);

	return lista->tamano;
}

void *consumidor(void *arg) {
	while(1){
		int n = supresion(list, 0);
		
	}
	sleep(1);
}

void *productor(void *arg) {
	while(1){
		char dato = 'a';
		int n = insercion(list, dato);
	}
	sleep(1);
}






