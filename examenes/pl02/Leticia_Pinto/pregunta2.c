#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define Elemeto char

pthread_mutex_t mutex;

int tamaño=0;

sem_t espacios_usados;

typedef struct ListaEnlazada
{
    Elemento *inicio;
    Elemento *fin;
    int tamaño;  
    Lista;
        
}

int insercion(Lista * lista, char *dato);
int supresion(Lista * lista, int pos);


int main(){

     
    pthread_t thread_insercion1;
    pthread_t thread_insercion2;
    pthread_t thread_supresion1;
    pthread_t thread_supresion2;
    
    pthread_mutex_init(&mutex, NULL);
    sem_init(&espacios_usados,0,0);
    
    pthread_create(&thread_insercion1,NULL,insercion,NULL);
    pthread_create(&thread_insercion2,NULL,insercion,NULL);
    pthread_create(&thread_supresion1,NULL,supresion,NULL);
    pthread_create(&thread_supresion2,NULL,supresion,NULL);
    
    pthread_join(&thread_insercion1,NULL);
    
    
    
    return 0;

}

int insercion(Lista * lista, char *dato)
{

    pthread_mutex_lock(&mutex);
    lista.fin=*dato;
    tamaño++;
    sem_post(&espacios_usados);
    pthread_mutex_lock(&mutex);
    
}

int supresion(Lista * lista, int pos)
{
    
    sem_wait(&espacios_usados);
    pthread_mutex_lock(&mutex);
    
    int i=0;
    
    while(i!=pos)
    {
        lista=lista.inicio;
        i++;
    }
    list.inicio=NULL;
    tamaño--;
    pthread_mutex_unlock(&mutex);
    
}



