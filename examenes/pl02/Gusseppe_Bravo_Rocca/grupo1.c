#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//Creo las variables semaforo
sem_t mutex;
sem_t regionCritica;

//Variables condicionales
pthread_cond_t condLeer;


//numero de lectores
int n_lectores = 0;


void escribiendo() {
	printf("Escribiendo\n");
}

void leyendo() {
	printf("Leyendo\n");
}

void *lector(void *arg) {
	while(1) {
		sem_wait(&mutex);
		
		leyendo();
		if(n_lectores == 1);
			//pthread_cond_t(&condLeer, &mutex);	
		sem_post(&mutex);
		n_lectores++;


		sleep(1);
	}
	
}

void *escritor(void *arg) {
	while(1) {
		sem_wait(&regionCritica);
		escribiendo();
		sem_post(&regionCritica);
		sleep(1);
	}
		
}

int main() {
	//inicializo los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&regionCritica, 0, 1);

	//Creo variables tid threads
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	//creo los threads
	
	pthread_create(&thread1, NULL, escritor, NULL);
	pthread_create(&thread2, NULL, lector, NULL);
	pthread_create(&thread3, NULL, lector, NULL);

	//espero a que finalice los threads
	pthread_join(thread1, NULL);

	//termino el main
	pthread_exit(NULL);


}






