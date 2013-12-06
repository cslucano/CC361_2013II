#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
char buffer[100];
int indice;
void *grabar()
{
    while(1){
        int i;
        for(i=0;i<indice;i++)
            printf("%c",buffer[i]);
        printf("\n");
        sleep(1);
    }
}
int main(){
    pthread_t thread_grabar;
    pthread_create(&thread_grabar,NULL,grabar,NULL);
    indice = 0;
    char c = 'a';
    while(scanf("%c",&c)){
        if(c=='i'){
            while(scanf("%c",&c)){
                if(c!='\n'){
                    if(indice < 100){
                        buffer[indice]=c;
                        indice++;
                    }
                }
                else{
                    break;
                }
            }
        }
        else if (c=='s'){
            if(indice >= 0){
                indice--;
            }
        }

    }
return 0;
}
