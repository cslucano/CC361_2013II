#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

char buffer[100];
int indice;

void *grabar(){

while(1){
    int i;
    for(i=0;i<=indice;i++)    
        {printf("%c",buffer[i]);
        }
    printf("\n");
    sleep(5);
    }    

}



int main(){

pthread_t thread_grabar;
pthread_create(&thread_grabar,NULL,grabar,NULL);

int i;
indice=-1;
char c='a';
char op,aux;


while(1){
        
    printf("\n\n");
    printf("i.- Ingresar\ns.-Sacar\n");
    gets(&op);

        if(op=='i'){
        
        scanf("%c", &c);
        indice++;
        buffer[indice]=c;
        
        printf("\n");
        }

        else if(op=='s'){
        printf("Se saco el elemento: %c",buffer[indice]);
        indice--;
        printf("\n");    
        }


        for(i=0;i<=indice;i++)    
            printf("%c",buffer[i]);
        
  }



return 0;
}
