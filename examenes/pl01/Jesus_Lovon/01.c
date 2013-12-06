#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char buffer[100];
int indice;

void * grabar(){
    while(1){
        int i;
        for(i = 0; i <=  indice; i++)
            printf("%c", buffer[i]);
        
        //para decir que ya se terminó de escribir y se puede pasar a imprimir
        printf("\n");
        //también se puede usar: (para decir que ya acabo y cuando se imprima no saldrá con el salto de línea)
        //fflush(stdout);               
        sleep(5);
    }
}

int main(){
    pthread_t thread_grabar;
    pthread_create(&thread_grabar, NULL, grabar, NULL);
    
    indice = -1;
    char c = 'a';
    char d = 'v';
    printf("menu:\n 1.- borrar elemento\n 2.- ingresar elemento\n");
    while(1/*gets(&c)*/){
        gets(&c);

        if(c=='1'){
            printf("%c\n", buffer[indice]);
            indice--;
        }
        else
        if(c == '2'){
            indice++;
            gets(&d);
            buffer[indice] = d;
        }
        
    }
    return 0;
}
