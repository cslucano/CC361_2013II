#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int lectores;
sem_t mutex;
sem_t regioncritica;


struct nodo{
   char   info;
   //int    tam;
   struct nodo *enlace;
};
typedef struct nodo lista;
typedef lista* ptrLista;

void insercion( char);
void supresion(int);
void recorrido();

ptrLista ptrInicio = NULL;



void insertar(){
while(1)
  {
    char c = 'a' + rand()%24;
    insercion(c);
    recorrido(ptrInicio);
    sleep(1);
  }
}

void borrar(){
while(1){
 supresion(1);
 printf("Elemento [1] de la lista borrado\n");
 sleep(1);
 }
}

void* insert(){
    while(1){
        sem_wait(&mutex);
        lectores++;
        if(lectores==0)
          sem_wait(&regioncritica);
        sem_post(&mutex);
        insertar();
        sem_wait(&mutex);
        lectores--;
        if(lectores==1)
          sem_post(&regioncritica);
        sem_post(&mutex);
        sleep(1);
    }
}

void* delete(){
    while(1){
        sem_wait(&regioncritica);
        borrar();
        sem_post(&regioncritica);
        sleep(1);
    }
}


int main(){
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;
    
    lectores=0;
    //insercion('d');
    //insercion('e');
    sem_init(&mutex,0,1);
    sem_init(&regioncritica,0,1);
    pthread_create(&thread_escritor1, NULL, insert, NULL );
    pthread_create(&thread_escritor2, NULL, insert, NULL );
    pthread_create(&thread_lector1, NULL, delete, NULL );
    pthread_create(&thread_lector2, NULL, delete, NULL );
        
    pthread_join(thread_lector1, NULL);
    //ptrInicio->tam=0;
    
    /*insercion('d');
    insercion('c');
    insercion('f');
    recorrido(ptrInicio);
    supresion(1);
      recorrido(ptrInicio);*/
    //printf("tam=%d\n",ptrInicio->tam);
 return 0;


}


void insercion(char dato){
ptrLista nuevo,aux;   
nuevo = malloc(sizeof(lista));
nuevo->info   = dato;
nuevo->enlace = NULL;
aux = ptrInicio;
 if(aux == NULL) {ptrInicio= nuevo;}//lista vacia
 else{
   while(aux->enlace!=NULL) aux=aux->enlace;
   aux->enlace=nuevo;
  }
 //(*ptrIni)->tam++; 
}
void recorrido(){
  ptrLista actual=ptrInicio;
  if (actual == NULL)
     printf("Lista Vacia\n");
  else{
        
        //recorremos la lista
        while (actual != NULL){
            printf("%c ==> ",actual->info);
            actual = actual->enlace;   
        }   
       printf("NULL\n"); 
  }
  
}
void supresion(int pos){
ptrLista aux1,aux2;int i;
aux1=ptrInicio;
aux2=ptrInicio;
if(ptrInicio==NULL) printf("Lista vacia, no se puede borrar\n");
else{
for(i=0;i<pos;i++) {aux1=aux2;aux2=aux2->enlace;}
aux1->enlace=aux2->enlace;
aux2=NULL;}
}

