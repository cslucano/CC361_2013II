#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n_lectores;
sem_t mutex;
sem_t regionVacía;

void leer()
{
  printf("Leyendo... %d\n", n_lectores);
}
void escribir()
{
  printf("Escribiendo ...\n");
}

void * lector()
{
    while(1){
        sem_wait(&mutex);
        n_lectores++;
        if(n_lectores == 1)
          sem_wait(&regionVacía);
        sem_post(&mutex);

        leer();

        sem_wait(&mutex);
        n_lectores--;
        if(n_lectores == 0)
          sem_post(&regionVacía);
        sem_post(&mutex);
        sleep(1);
    }
}

void * escritor()
{
    while(1){
        sem_wait(&regionVacía);
        escribir();
        sem_post(&regionVacía);
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

    n_lectores = 0;
    sem_init(&mutex,0,1);
    sem_init(&regionVacía,0,1);

    pthread_create(&thread_lector1, NULL, lector, NULL );
    pthread_create(&thread_lector2, NULL, lector, NULL );
    pthread_create(&thread_lector3, NULL, lector, NULL );
    pthread_create(&thread_escritor1, NULL, escritor, NULL );
    pthread_create(&thread_escritor2, NULL, escritor, NULL );
	 pthread_create(&thread_escritor2, NULL, escritor, NULL );

    pthread_join(thread_lector1, NULL);

    return 0;
}
