#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int n_lectores = 0;
sem_t sem1;
sem_t sem2;

void leer();
void escribir();
void * lector ();
void * escritor();

int main(){
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    pthread_t thread_lector3;
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;
    
    sem_init(&sem1,0,1);
    sem_init(&sem2,0,1);
    pthread_create(&thread_lector1, NULL, lector, NULL );
    pthread_create(&thread_lector2, NULL, lector, NULL );
    pthread_create(&thread_lector3, NULL, lector, NULL );
    pthread_create(&thread_escritor1, NULL, escritor, NULL );
    pthread_create(&thread_escritor2, NULL, escritor, NULL );

    pthread_join(thread_lector1, NULL);
    return 0;
}
void leer(){
	printf("Reading\n");
}
void escribir(){
	printf("Writing\n");
}
void *lector (){

	while (1){
	// Sección no crítica
	sem_wait(&sem1);
		n_lectores++;
	if (n_lectores == 1)
		sem_wait(&sem2);
	sem_post(&sem1);

	// Lectura
	leer();
	sem_wait(&sem1);
	n_lectores--;
	if (n_lectores == 0 )
		sem_post(&sem2);
	sem_post(&sem1);	
	}
}
void * escritor()
{
    while(1){
        sem_wait(&sem1);
        escribir();
        sem_post(&sem2);
    }
}

