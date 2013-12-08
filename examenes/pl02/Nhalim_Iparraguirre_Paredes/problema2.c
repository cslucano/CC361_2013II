#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX 100
#define N_USUARIOS 1
// 		TIPOS			//
typedef char Elemento;
typedef struct ListaEnlazada
{
	Elemento A[MAX];
	int next[MAX];
	int back[MAX];
	int talla;
	
	//next = talla;
	//back = talla - 2;
	//actual = talla -1; 
}Lista;
/////////////////////////////////////////
//***************************************
sem_t operation;
int usuarios = 0;
//***************************************


void init(Lista * l);
void *insercion(Lista * lista, char dato);
void  *supresion(Lista * lista, int pos);

int main(){
    pthread_t insertar[100];
    pthread_t suprimir[100];
    Lista L1;
    init(&L1);
    sem_init(&operation,0,1);
    int i=0;
    for(;i<100;i++){
    	pthread_create(&(insertar[i]), NULL, insercion, NULL );
    	pthread_create(&(suprimir[i]), NULL, supresion, NULL );
    }

	return 0;
}

void *insercion(Lista * lista, char dato){
	sem_wait(&operation);
	if( lista->talla < MAX && lista->talla >= 0 ){
		lista->A[lista->next[lista->talla]] = dato;
		lista->talla ++;
		lista->next[lista->talla] = lista->next[lista->talla]+1;
	}
	printf("insertó\n");
	sem_post(&operation);
}
void *supresion(Lista * lista, int pos){
	sem_wait(&operation);
	if( lista->talla > 0 ){
		
		///eliminamos
		lista->A[lista->next[pos]] = 0 ;
		/// apuntamos al final
		lista->next[lista->back[pos]] = lista->back[lista->next[pos]];
		
		lista->talla --;
	}
	printf("suprimió\n");
	sem_post(&operation);
}
void imprimir(Lista * l){
	int i;
	for( i = 0; i < MAX ; i++){
	 printf("%c-\n",l->A[l->next[i]]);
	}
}
void init(Lista * l){
	int i;
	l->talla = 0;
	for(i=0;i<MAX;i++){
		l->next[i] = i+1;
		l->back[i] = i-1;
	}
	l->back[0] = MAX - 1;
	l->next[MAX-1] = 0;	
}

