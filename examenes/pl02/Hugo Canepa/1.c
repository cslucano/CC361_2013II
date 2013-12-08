#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int lectores;
sem_t mutex;
sem_t regioncritica;

void leer(){
printf("%d esta leyendo\n", lectores);
}

void escribir(){
printf("escribiendo\n");
}

void* lector(){
    while(1){
        sem_wait(&mutex);
        lectores++;
        if(lectores==1)
          sem_wait(&regioncritica);
        sem_post(&mutex);

        
        leer();
        

        sem_wait(&mutex);
        lectores--;
        if(lectores==0)
          sem_post(&regioncritica);
        sem_post(&mutex);
        sleep(1);
    }
}

void* escritor(){
    while(1){
        sem_wait(&regioncritica);
        escribir();
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
sem_init(&mutex,0,1);
sem_init(&regioncritica,0,1);

pthread_create(&thread_lector1, NULL, lector, NULL );
pthread_create(&thread_lector2, NULL, lector, NULL );
pthread_create(&thread_escritor1, NULL, escritor, NULL );
pthread_create(&thread_escritor2, NULL, escritor, NULL );

pthread_join(thread_lector1, NULL);

return 0;

    
}



