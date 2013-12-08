#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int dato=15;
int n_lectores = 0;
sem_t sem_lec;
sem_t regioncriticaVacia;


void* Lector(void){
	sem_wait(&sem_lec);
	n_lectores = n_lectores+1;
	if(n_lectores==1)
		sem_wait(&regioncriticaVacia);
	sem_post(&sem_lec);
	
	printf("%d\n",dato);
	
	sem_wait(&sem_lec);
	n_lectores=n_lectores-1;
	if(n_lectores==0)
		sem_post(&regioncriticaVacia);
	sem_post(&sem_lec);
	pthread_exit(0);
}

void* Escritor(void){
	sem_wait(&regioncriticaVacia);
	dato = dato+5;
	sem_post(&regioncriticaVacia);
	
	pthread_exit(0);	
}

void main(void){
int c=0;
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	pthread_t th4;
				
	sem_init(&regioncriticaVacia,0,1);
	sem_init(&sem_lec,0,1);

	pthread_create(&th1,NULL,Lector,NULL);
	pthread_create(&th2,NULL,Escritor,NULL);
	pthread_create(&th3,NULL,Lector,NULL);
	pthread_create(&th4,NULL,Escritor,NULL);
		
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	pthread_join(th4,NULL);

	sem_destroy(&regioncriticaVacia);
	sem_destroy(&sem_lec);	

	exit(0);
}
