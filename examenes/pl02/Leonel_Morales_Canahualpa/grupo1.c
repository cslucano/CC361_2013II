#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int n_lectores;
sem_t mutex;
sem_t regioncriticaVacia;

void leer()
{
  printf("leyendo %d\n", n_lectores);
}
void escribir()
{
  printf("escribiendo\n");
}

void* lector(){
	while(1){
		sem_wait(&mutex);
			n_lectores++;
			if(n_lectores==1)	sem_wait(&regioncriticaVacia);
		sem_post(&mutex);
		leer();
		sem_wait(&mutex);
			n_lectores--;
			if(n_lectores==0)	sem_post(&regioncriticaVacia);
		sem_post(&mutex);

		sleep(1);
	}
}

void* escritor(){
	while(1){
		sem_wait(&regioncriticaVacia);
		escribir();
		sem_post(&regioncriticaVacia);

		sleep(1);
	}
}

int main(){
	n_lectores = 0;
	pthread_t thread_lector, thread_lector2;
	pthread_t thread_escritor;
	sem_init(&mutex,0,1);
	sem_init(&regioncriticaVacia,0,1);

	pthread_create(&thread_lector, NULL, lector, NULL );
	pthread_create(&thread_lector2, NULL, lector, NULL );
	pthread_create(&thread_escritor, NULL, escritor, NULL );

	pthread_join(thread_lector, NULL);

	return 0;
}
