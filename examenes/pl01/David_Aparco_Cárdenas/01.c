#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
char buffer[100];
int indice;

void * grabar()
{
    while(1){
    int i;
    for(i=0; i<=indice;i++){
        printf("%c", buffer[i]);
    }
    printf("\n");
    sleep(1);
    }
}


int main(){
    pthread_t thread_grabar; 
    pthread_create(&thread_grabar, NULL, grabar, NULL); 
    int option;
    printf("\t\tMENU\n1) i -> ingresar\n2) s -> sacar\n");
    indice = 0;
   char c;
   while(gets(&c))
   {
        switch(c)
        {
            case 'i': scanf("%c", &c);
                         buffer[indice] = c;
                         indice++;
                         break;
            case 's': 
                         printf("%c\n", buffer[indice]);
                         indice--;
                         break;
        }
                        
   } 
   return 0;
}
