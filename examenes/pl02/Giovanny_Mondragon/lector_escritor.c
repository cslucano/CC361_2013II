#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int lectores;
sem_t mutex;
sem_t rcvacia;

void leer()
{
  printf("Leyendo %d\n", lectores);
}


void escribir()
{
  printf("Escribiendo...\n");
}


void * lector()
{
    while(1){
        sem_wait(&mutex);
        lectores++;

        if(lectores==1)
          sem_wait(&rcvacia);
        sem_post(&mutex);

        // Regio Critica
        leer();

        sem_wait(&mutex);
        lectores--;

        if(lectores==0)
          sem_post(&rcvacia);
        sem_post(&mutex);

        sleep(1);
    }
}

void * escritor()
{
    while(1){

        sem_wait(&rcvacia);
        escribir();
        sem_post(&rcvacia);

        sleep(1);
    }
}

int main()
{
	
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;

		
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    pthread_t thread_lector3;
	pthread_t thread_lector4;

    lectores = 0;
    sem_init(&mutex,0,1);///mutex=semaforo(1)

    sem_init(&rcvacia,0,1);///cuarto_vacio=semaforo(1)

	
    pthread_create(&thread_escritor1, NULL, escritor, NULL );
    pthread_create(&thread_escritor2, NULL, escritor, NULL );

    pthread_create(&thread_lector1, NULL, lector, NULL );
    pthread_create(&thread_lector2, NULL, lector, NULL );
    pthread_create(&thread_lector3, NULL, lector, NULL );
	pthread_create(&thread_lector3, NULL, lector, NULL );	

    pthread_join(thread_escritor1, NULL);

    return 0;
}
