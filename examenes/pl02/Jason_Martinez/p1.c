#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int n_lectores;

sem_t mutex;
sem_t regioncriticaVacia;

void leer(){
    printf("Lectores: %d\n", n_lectores);
}

void escribir(){
    puts("Escribiendo");
}

void *lector(){
    while(1){
        sem_wait(&mutex);
        n_lectores++;
        if(n_lectores == 1)
            sem_wait(&regioncriticaVacia);
        sem_post(&mutex);

        //Inicio Zona Critica
        leer();
        //Fin Zona Critica

        sem_wait(&mutex);
        n_lectores--;
        if(n_lectores == 0)
            sem_post(&regioncriticaVacia);
        sem_post(&mutex);
        sleep(1);
    }
}

void *escritor(){
    while(1){
        sem_wait(&regioncriticaVacia);
        
        //Inicio Zona Critica
        escribir();
        //Fin Zona Critica
        
        sem_post(&regioncriticaVacia);
        sleep(1);
    }
}

int main(){
    pthread_t lector1;
    pthread_t lector2;
    pthread_t lector3;
    pthread_t escritor1;
    pthread_t escritor2;

    sem_init(&mutex, 0, 1);
    sem_init(&regioncriticaVacia, 0, 1);

    pthread_create(&lector1, NULL, &lector, NULL);
    pthread_create(&lector2, NULL, &lector, NULL);
    pthread_create(&lector3, NULL, &lector, NULL);
    pthread_create(&escritor1, NULL, &escritor, NULL);
    pthread_create(&escritor2, NULL, &escritor, NULL);
    pthread_join(lector1, NULL);
}
