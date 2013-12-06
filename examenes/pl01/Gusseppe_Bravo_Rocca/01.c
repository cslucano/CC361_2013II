#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1
char buffer[100];
int indice;
void* grabar() {
while(true) {
int i;	
for (i = 0; i < indice; ++i) {
printf("[%c] ", buffer[i]);
}
fflush(stdout);

sleep(2);
}
}

int main(int argc, char const *argv[])
{
pthread_t thread_grabar;
pthread_create(&thread_grabar, NULL, grabar, NULL);

indice = 0;
char c = 'a';

while(gets(&c)) {	
switch(c) {
case 'i':
gets(&c);
buffer[indice] = c;	
indice++;
break;
case 's':
printf("%c\n", buffer[indice-1]);
indice--;
break;
}
}	
return 0;
}
