#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[100];
int indice;
pthread_mutex_t mutex;
sem_t sem_espacios_vacios;
sem_t sem_espacios_ocupados;

void agregar(int n);
void quitar();

void * productor()
{
 while(1)
 {
   int n = 5 +rand()*100;
   agregar(n);
   sleep(1);
 }
}
void * consumidor()
{
 while(1)
 {
   quitar();
   sleep(1);
 }
}

void * imprimir()
{
   while(1){
       int i;
       printf("%d",indice);
       printf("\n");
       sleep(1);
   }
}

int main()
{
   pthread_t thread_consumidor;
   pthread_t thread_productor1;
   pthread_t thread_productor2;

   indice = 0;
   pthread_mutex_init(&mutex,NULL);
   sem_init(&sem_espacios_vacios,0,100);
   sem_init(&sem_espacios_ocupados,0,0);

   pthread_create(&thread_consumidor, NULL, consumidor, NULL );
   pthread_create(&thread_productor1, NULL, productor, NULL );
   pthread_create(&thread_productor2, NULL, productor, NULL );

   pthread_join(thread_consumidor, NULL);

   return 0;
}

void agregar(int n)
{
sem_wait(&sem_espacios_vacios);
pthread_mutex_lock(&mutex);
       buffer[indice] = n;
       indice++;
       printf("%d\n",indice);
sem_post(&sem_espacios_ocupados);
pthread_mutex_unlock(&mutex);
}

void quitar()
{
sem_wait(&sem_espacios_ocupados);	  
pthread_mutex_lock(&mutex);
       indice--;
       printf("%d\n",indice);
sem_post(&sem_espacios_vacios);
pthread_mutex_unlock(&mutex);

}
