#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t isEmpty;

typedef struct Node{
    char val;
    struct Node *next;
    struct Node *prev;
}Elemento;

typedef struct ListaEnlazada
{
    Elemento *inicio;    
    Elemento *fin;
    int tamanho;
}LL;

typedef LL * Lista;

Lista T;

void init(Lista * lista);
int insercion(Lista * lista, char *dato);
char supresion(Lista * lista, int pos);

void *productor(){
    while(1){
        pthread_mutex_lock(&mutex);
        char c = (char)('a' + rand()%26);
        int pos = insercion(&T, &c);
        printf(">> insertado: %c en la posicion %d\n", c, pos);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        sem_post(&isEmpty);
    }
}

void *consumidor(){
    while(1){
        sem_wait(&isEmpty);

        pthread_mutex_lock(&mutex);
        int pos = 1 + rand()%((T)->tamanho);
        char c = supresion(&T, 1);
        printf("<< suprimido: %c de la posicion %d\n", c, pos);
        pthread_mutex_unlock(&mutex);
        sleep(1);

    }
}

int main(){
    init(&T);

    pthread_t productor1;
    pthread_t productor2;
    pthread_t productor3;
    
    pthread_t consumidor1;
    pthread_t consumidor2;
    pthread_t consumidor3;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&isEmpty, 0, 0);

    pthread_create(&productor1, NULL, &productor, NULL);
    pthread_create(&productor2, NULL, &productor, NULL);
    
    pthread_create(&consumidor1, NULL, &consumidor, NULL);
    pthread_create(&consumidor2, NULL, &consumidor, NULL);
    pthread_create(&consumidor3, NULL, &consumidor, NULL);

    pthread_join(productor1, NULL);
}

void init(Lista * lista){
    *lista = malloc(sizeof(lista));
    Elemento *p = malloc(sizeof(Elemento));
    (*lista)->inicio = p;
    ((*lista)->inicio)->next = NULL;
    ((*lista)->inicio)->prev = NULL;
    
    Elemento *q = malloc(sizeof(Elemento));
    (*lista)->fin = q;
    ((*lista)->fin)->next = NULL;
    ((*lista)->fin)->prev = NULL;
    (*lista)->tamanho = 0;
}

int insercion(Lista * lista, char *dato)
{
    Elemento *p = malloc(sizeof(Elemento));
    p->val = *dato;
    p->next = NULL;
    p->prev = (*lista)->fin;
    ((*lista)->fin)->next = p;
    (*lista)->fin = p;
    if((*lista)->tamanho == 0){
        (*lista)->inicio = p;
        p->prev = (*lista)->inicio;
    }
    (*lista)->tamanho += 1;
    return (*lista)->tamanho;
}

char supresion(Lista * lista, int pos){
    Elemento *p = malloc(sizeof(Elemento));
    Elemento *q = malloc(sizeof(Elemento));
    p = (*lista)->inicio;
    q = NULL;
    pos--;
    while(pos>0){
        q = p;
        p = p->next;
        pos--;
    }
    char r;
    r = p->val;
    if(p->next != NULL)
        (p->next)->prev = q;
    if(q == NULL)
        (*lista)->inicio = p->next;
    else
    q->next = p->next;
    (*lista)->tamanho -= 1;
    return r;
}
