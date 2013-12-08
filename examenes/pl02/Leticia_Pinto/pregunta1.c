#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

pthread_mutex_t mutex;
sem_t roomEmpty;

int n_lectores=0;

void *escritor(){
    
    while(1){
        
        //zona critica:
        //pthread_mutex_lock(&mutex);
        sem_wait(&roomEmpty);
        printf("Escribiendo\n");
        
        sem_post(&roomEmpty);
        sleep(1);
        //pthread_mutex_unlock(&mutex);
        
    }    
}

void *lector(){


    while(1){
        
        sem_post(&roomEmpty);
        pthread_mutex_lock(&mutex);
        
        printf("Leyendo %d\n",n_lectores);
        n_lectores++;
         
        pthread_mutex_unlock(&mutex);
        sleep(1);
        
        
    }
}

int main(){
    
    pthread_t thread_escritor1;
    pthread_t thread_escritor2;
    pthread_t thread_lector1;
    pthread_t thread_lector2;
    
    pthread_mutex_init(&mutex, NULL);
    sem_init(&roomEmpty,0,100);
    
    pthread_create(&thread_escritor1,NULL,escritor,NULL);
    pthread_create(&thread_escritor2,NULL,escritor,NULL);
    pthread_create(&thread_lector1,NULL,lector,NULL);
    pthread_create(&thread_lector2,NULL,lector,NULL);
    
    pthread_join(thread_escritor1,NULL);
    
    return 0;
    
}










