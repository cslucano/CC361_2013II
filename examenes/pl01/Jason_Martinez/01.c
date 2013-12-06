#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_P 100

typedef struct Stack{
 char buffer[MAX_P];
 int cur;
} Stack;

Stack pila;

void init(){
 pila.cur = 0;
}

void pop(){
 if(pila.cur <= 0){
   puts("Stack Overflow");  
   return;
 }
 pila.cur--;
}
void push(char c){
 if(pila.cur>=MAX_P){
   puts("Stack Underflow");  
   return;
 }
 pila.buffer[pila.cur++] = c;
}
int size(){
 return pila.cur;
}


struct Stack S;

void * grabar(){
 while(1){
   int i;
   for(i=0; i<size(); i++)
     printf("%c", pila.buffer[i]);
   printf("\n");
   sleep(5);
 }
}

int main(){
 init();
 pthread_t thread_grabar;
 pthread_create(&thread_grabar, NULL, grabar, NULL);
 puts("i: Insertar    s:Sacar");
 char comand, in;
 while(gets(&comand)){
   switch(comand){
     case 'i':
       gets(&in);
       push(in);
       break;
     case 's':
       pop();
       break;
   }
 }
 return 0;
}
