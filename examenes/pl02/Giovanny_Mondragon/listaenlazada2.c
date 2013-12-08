#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int indice;
// Declaramos Mutex
pthread_mutex_t mutex;
sem_t semaforo_inserta;
sem_t semaforo_borra;



typedef struct _nodo {
	int valor;
	struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;
/* Funciones con listas: */

Lista lista = NULL;
Lista fin = NULL;



void insercion(Lista *lista,Lista *ultimo, int v);

int ListaVacia(Lista l);
void BorrarLista(Lista *);
void MostrarLista(Lista l);

void supresion( Lista *lista , int pos);


void * insertando()
{
  while(1)
  {
    int n;
	n = 1 + rand()%24;
    insercion(&lista,&fin, n);;
    sleep(1);
  }
}
void * borrando()
{
  while(1)
  {	
	int n;
	n = 1 + rand()%7;
    supresion(&lista,n);
    sleep(1);
  }
}

void * imprimir()
{
    while(1){
       MostrarLista(lista);
        sleep(1);
    }
}




int main()
{
	pthread_t thread_imprimir;
	pthread_t thread_inserta;
    pthread_t thread_borra;
	pNodo p;
	
	indice =0;
	
    pthread_mutex_init(&mutex, NULL);
		
	
    sem_init(&semaforo_inserta, 0, 10);
    sem_init(&semaforo_borra, 0, 0);
		
	
    pthread_create(&thread_inserta, NULL, insertando, NULL );
    pthread_create(&thread_borra, NULL, borrando, NULL );
	pthread_create(&thread_imprimir, NULL, imprimir, NULL );	


	  pthread_join(thread_imprimir, NULL);

//	insercion(&lista,&fin, 20);
//	insercion(&lista,&fin, 10);	
//	insercion(&lista,&fin, 40);
//	insercion(&lista,&fin, 30);
//	insercion(&lista,&fin, 60);	

//	MostrarLista(lista);
	

	

//	MostrarLista(lista);
//	Borrar(&lista,10);
//	Borrar(&lista,15);
	
	//supresion(&lista,4);
	
//	MostrarLista(lista);
	//BorrarLista(&lista);
return 0;
}





void insercion(Lista *lista,Lista *ultimo, int v)
{
	pNodo nuevo, anterior;
/* Crear un nodo nuevo */
	nuevo = (pNodo)malloc(sizeof(tipoNodo));
	nuevo->valor = v;

/* Si la lista está vacía */
	if(ListaVacia(*lista)) {
		nuevo->siguiente = *lista;
		*lista = nuevo;
		*ultimo=nuevo;
	}

else {
	anterior = *ultimo;
	nuevo->siguiente = NULL;
	anterior->siguiente = nuevo;
	*ultimo=nuevo;
		}

}





void supresion(Lista *lista, int pos)
{
	pNodo anterior, nodo;
	int i;
	nodo = *lista;
	anterior = NULL;

	for(i=0;i<pos-1;i++){
			anterior=nodo;
			nodo=nodo->siguiente;
	}	

	/* Borrar el nodo */
	if(!anterior) /* Primer elemento */
		*lista = nodo->siguiente;
	else /* un elemento cualquiera */
		anterior->siguiente = nodo->siguiente;
	free(nodo);


}



int ListaVacia(Lista lista)
{
	return (lista == NULL);
}

void BorrarLista(Lista *lista)
{
	pNodo nodo;

	while(*lista) {
	nodo = *lista;
	*lista = nodo->siguiente;
	free(nodo);
	}	

}


void MostrarLista(Lista lista)
{
	pNodo nodo = lista;
	if(ListaVacia(lista)) printf("Lista vacía\n");
	else {
		while(nodo) {
		printf("%d -> ", nodo->valor);
		nodo = nodo->siguiente;
		}
printf("\n");
}
}









