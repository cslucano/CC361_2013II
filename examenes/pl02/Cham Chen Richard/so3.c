#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n_lectores;
sem_t mutex;
sem_t regioncriticaVacia;

void leer()
{
  printf("Lectores ahora: %d\n", n_lectores);
}
void escribir1()
{
  printf("Escribiendo..Escritor #1\n");
}

void escribir2()
{
  printf("Escribiendo..Escritor #2\n");
}

void escribir3()
{
  printf("Escribiendo..Escritor #3\n");
}

void * lector()
{
    while(1){
        sem_wait(&mutex);
        n_lectores++;
        
	if(n_lectores==1)
          sem_wait(&regioncriticaVacia);
        
	sem_post(&mutex);
        leer();
	sem_wait(&mutex);
        n_lectores--;
        
	if(n_lectores==0)
          sem_post(&regioncriticaVacia);
        
	sem_post(&mutex);
        sleep(1);
    }
}

void * escritor1()
{
    while(1){
        sem_wait(&regioncriticaVacia);
        escribir1();
        sem_post(&regioncriticaVacia);
        sleep(1);
    }
}

void * escritor2()
{
    while(1){
        sem_wait(&regioncriticaVacia);
        escribir2();
        sem_post(&regioncriticaVacia);
        sleep(1);
    }
}

void * escritor3()
{
    while(1){
        sem_wait(&regioncriticaVacia);
        escribir3();
        sem_post(&regioncriticaVacia);
        sleep(1);
    }
}


int main()
{
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    pthread_t thread_lector3;
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;
    pthread_t thread_escritor3;
//
    n_lectores = 0;
    sem_init(&mutex,0,1);//0,1:semaforo para proteger contador de lectores
    sem_init(&regioncriticaVacia,0,1);//protege region critica
//threads
    pthread_create(&thread_lector1, NULL, lector, NULL );
    pthread_create(&thread_lector2, NULL, lector, NULL );
    pthread_create(&thread_lector3, NULL, lector, NULL );
    pthread_create(&thread_escritor1, NULL, escritor1, NULL );
    pthread_create(&thread_escritor2, NULL, escritor2, NULL );
    pthread_create(&thread_escritor3, NULL, escritor3, NULL );
    pthread_join(thread_lector1, NULL);

    return 0;
}
