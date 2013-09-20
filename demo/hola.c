#include <stdio.h>
#include <stdlib.h>
int factorial(int n)
{
  printf("&n %p\n", &n );
  if(n>1)
    return n * factorial(n-1);
  return 1; 
}
int main()
{
  int i = 5;
  printf("&i %p\n",&i );
  printf("&main %p\n", main );
  printf("&factorial %p\n", factorial );
  factorial(5);
  while(i>1)
  {
    int* o = malloc(sizeof(int));
    printf("%p\n", o);
    i--;
  }
  char c;
  gets(&c);
  return 0;
}
