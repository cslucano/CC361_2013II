#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
char buffer[100];
int indice;

void* grabar()
{
        while(1)
        {        int i;
                for(i=0;i<=indice;i++)
                {
                        printf("%c",buffer[i]);
                }
                printf("\n");
                sleep(1);
        }
}

int main()
{
        pthread_t thread_grabar;
        pthread_create(&thread_grabar,NULL,grabar,NULL);
        char opc;    
        indice=0;
        char c= 'a';
        int aux;
        printf("\t\tMENU\n");        
        
        while(1)
        {        
                printf("i:ingresar\ns:sacar\n");
                scanf("%c",&opc);
                switch(opc)
                {
                        case 'i':        while(gets(&c))
                                                {        if (c=='s')
                                                        {     printf("se saca %c\n\n",buffer[indice-1]);
                                                        indice=indice-2;
                                                                break;
                                                        }
                                                        buffer[indice]=c;
                                                        indice++;
                                                }
                                                break;
                                            
                        case 's':    
                                                printf("se saca %c\n\n",buffer[indice]);
                                                indice=indice-1;
                                                break;

                }
        }        
        return 0;
}
