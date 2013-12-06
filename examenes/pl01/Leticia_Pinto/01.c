#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

char buffer[100];
int indice;

void * grabar()
{
    while(1)
    {
        int i;
        //printf("guardando...\n");
        for(i=0;i<indice;i++)
            printf("%c",buffer[i]);
        fflush(stdout);
        sleep(1);
    }
}


int main()
{
    
    printf("\t\tMENU");
    pthread_t thread_grabar;
    pthread_create(&thread_grabar,NULL,grabar,NULL); //4to: atributo
    
    printf("Opciones:\n");
    printf("Digite i para ingresar caracter:\n");
    printf("Digite e para extraer el ultimo caracter:\n");

    indice = 0;
    char p;
    while(gets(&p)){
        switch(p)
        {
            case 'i':
                    gets(&p);
                    buffer[indice]=p;
                    //printf("%c",buffer[indice]);
                    indice++;
                    break;
        
            case 's': 
                    indice--; 
                    printf("%c",buffer[indice]);
                    
                    break;  
        }
    }
    
    char c ='a';
    //char temp[10];
    /*while(gets(&c))
    {
        buffer[indice]=c;
        indice++;
    }*/
    return 0;
}
