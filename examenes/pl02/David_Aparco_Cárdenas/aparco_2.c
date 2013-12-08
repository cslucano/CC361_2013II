//Solo implemente la estructura.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct ElementoLista
{
  char *dato;
  struct ElementoLista * siguiente;

} Elemento;

typedef struct ListaIdentificar
{
  Elemento * inicio;
  Elemento * fin;
  int tamano;
} Lista;

void inicializacion (Lista * lista);
int insercion (Lista * lista, Elemento * actual, char *dato);
int supresion (Lista * lista, int pos);

int menu (Lista *lista,int *k);
void muestra (Lista * lista);


int main (void)
{
  char eleccion;
  char *nom;
  Lista *lista;
  Elemento *actual;

  if ((lista = (Lista *) malloc (sizeof (Lista))) == NULL)
    return -1;
  if ((nom = (char *) malloc (50)) == NULL)
    return -1;
  actual = NULL;
  eleccion = 'o';

  inicializacion (lista);
  int pos, k;

  while (1){
      eleccion = menu (lista, &k);
      switch (eleccion){
        case 1:
          printf ("Ingrese un Elemento: ");
          scanf ("%s", nom);
          getchar ();
          insercion (lista, lista->fin, nom);
          printf ("tamaño lista: %d Elementos: inicial = %s, final = %s\n", lista->tamano,
                  lista->inicio->dato, lista->fin->dato);
          muestra (lista);
          break;
		  case 2:
          do{
              printf ("Ingrese la posicion : ");
              scanf ("%d", &pos);
	    }
          while (pos < 1 || pos > lista->tamano);
          getchar ();
          supresion (lista, pos);
          if (lista->tamano != 0)
            printf ("%d Elementos:ini=%s,fin=%s\n", lista->tamano,
                    lista->inicio->dato, lista->fin->dato);
          else
            printf ("lista vacia\n");
          muestra (lista);
          break;

        case 3:
 
          muestra (lista);
          break;
		  case 4:
			 return 0;
      }
  }
  return 0;
}

void
inicializacion (Lista * lista)
{
  lista ->inicio = NULL;
  lista ->fin = NULL;
  lista ->tamano = 0;
}

int insercion (Lista * lista, Elemento * actual, char *dato){ // fin de lista
  Elemento *nuevo_Elemento;
  if ((nuevo_Elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;
  if ((nuevo_Elemento->dato = (char *) malloc (50 * sizeof (char)))
      == NULL)
    return -1;
  strcpy (nuevo_Elemento->dato, dato);

  if (lista -> tamano == 0){
    nuevo_Elemento->siguiente = NULL;
    lista -> inicio = nuevo_Elemento;
    lista -> fin = nuevo_Elemento;
    lista -> tamano++;
  }
	
  else{
  actual -> siguiente = nuevo_Elemento;
  nuevo_Elemento -> siguiente = NULL;
  lista -> fin = nuevo_Elemento;
  lista -> tamano++;
  }

  return 0;
}

int supresion (Lista * lista, int pos){ 
  if (lista -> tamano <= 1 || pos < 1 || pos >= lista -> tamano)
    return -1;
  int i;
  Elemento * actual;
  Elemento * sup_Elemento;
  actual = lista -> inicio;

  for (i = 1; i < pos; ++i)
    actual = actual -> siguiente;

  sup_Elemento = actual -> siguiente;
  actual -> siguiente = actual -> siguiente -> siguiente;
  if(actual -> siguiente == NULL)
          lista -> fin = actual;
  free (sup_Elemento -> dato);
  free (sup_Elemento);
  lista -> tamano--;
  return 0;
}

void muestra (Lista * lista){
  Elemento * actual;
  actual = lista -> inicio;
  while (actual != NULL){
      printf ("%s ", actual -> dato);
      actual = actual -> siguiente;
  }
}


int menu (Lista * lista, int * k){
  int eleccion;
  printf("\n\n********** MENU **********\n");
    printf ("1.Inserción\n");
    printf ("2.Supresión\n");
	 printf ("3.Mostrar\n");
	 printf ("4.Salir");

  printf ("\n\nElegir: ");
  scanf ("%d", &eleccion);
  getchar();
  return eleccion;
}


