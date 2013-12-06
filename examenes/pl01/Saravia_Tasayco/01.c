#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
char buffer[100];
int indice;
void * grabar(){
while(1){
  int i;
    for(i=0;i<=indice;i++){
     printf("%c",buffer[i]);
     }
     fflush(stdout);
    
    sleep(2);
}
}

int main(){
pthread_t thread_grabar;
pthread_create(&thread_grabar,NULL,grabar,NULL);
indice=0;
char c='a';
printf("Puede incrementar(i) o sacar(s)");
while(gets(&c))
    {
    if(c=='i')
        {
        printf("Agregar a la pila : ");
       gets(&c);
       buffer[indice] = c;
      }
      if(c=='s'){
      printf("sacar de la pila");
               printf("\n%c",buffer[indice-1]);
               indice--;
               printf("\n");
       }         
    indice++;
    }
    return 0;
}
