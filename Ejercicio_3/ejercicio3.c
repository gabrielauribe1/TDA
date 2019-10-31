#include<stdio.h>
#include<stdlib.h>

typedef struct nodo
{
  char dato, estado;
  int cant;
  struct nodo **dir;
}tiponodo;

void anadir_nodo(tiponodo *raiz,tiponodo *nuevo, char letra);
void desplegar_grafo(tiponodo *raiz, int c);
void buscar_nodo(tiponodo *raiz, int c, char buscado, tiponodo **aux);

//void liberar_memoria();

int main(void)
{
  char letra, buscado;
  tiponodo *raiz = NULL ,*nuevo, *aux=NULL;
  int Opcion, i, j, max, c=0;
  
  raiz=NULL;
  
  printf("Introduzca los nodos que desea insertar:\n");
  scanf("%d", &max);
  
  printf("Introduzca los nodos:\n");
  for(j=0; j<max; j++)
    {
      __fpurge(stdin);
      scanf("%c",&letra);
      if((letra>='a'&&letra<='z')||(letra>='A'&&letra<='Z'))
	{
	  nuevo=(struct nodo*)malloc(sizeof(struct nodo));
	  nuevo->dato=letra;
	  nuevo->dir=(tiponodo**)malloc(sizeof(tiponodo*)*4);
	  nuevo->cant=0;
	  for(i=0; i<4; i++)
	    {
	      nuevo->dir[i] = NULL;
	    }
	  if(raiz==NULL)
	    raiz=nuevo; 
	  else
	    anadir_nodo(raiz,nuevo, letra);
	}
    }
  
  do
    {
      system("clear");
      printf("Introduzca la opción deseada:\n");
      printf("1. Buscar nodo\n");
      printf("2. Desplegar grafo\n");
      printf("3. Salir\n");
      scanf("%d", &Opcion);
   
      switch(Opcion)
	{
       
	case 1:
	  printf("Introduzca la la letra(nodo) que desea buscar:\n");
	  scanf(" %c", &buscado);
	  buscar_nodo(raiz, c, buscado, &aux);

	  if(aux==NULL)
	    {
	      __fpurge(stdin);
	      printf("Ese nodo no existe\n");
	      getchar();
	    }

	  break;
	case 2:
	  printf("Grafo desplegado por orden:\n");
	  desplegar_grafo(raiz, c);
	  printf("\n");
	  __fpurge(stdin);
	  getchar();
	  break;
	case 3:
	  printf("Saliendo del programa\n");
	  exit(0);
	  break;
	default:
	  printf("Opción inválida.");
	  printf("Saliendo del programa\n");
	  exit(0);
	}
    }while(Opcion!=3);
  //liberar_memoria();
}

void anadir_nodo(tiponodo *raiz,tiponodo *nuevo, char letra)
{
  char buscado;
  int i, c=0;
  tiponodo *aux=NULL;

  do
    {
      aux=NULL;
      printf("A que nodo lo deseas conectar?\n");
      scanf(" %c", &buscado);
      buscar_nodo(raiz, c, buscado, &aux);

      if(aux==NULL)
	{
	  printf("Ese nodo no existe\n");
	}
    }while(aux==NULL);

  nuevo=(struct nodo*)malloc(sizeof(struct nodo));
  nuevo->dato=letra;
  nuevo->dir=(tiponodo**)malloc(sizeof(tiponodo*)*4);
  for(i=0; i<4; i++)
    {
      nuevo->dir[i] = NULL;
    }
  if(aux->cant < 4)
    {
      aux->dir[aux->cant]=nuevo;
      aux->cant = aux->cant + 1;
    }
  else
    printf("Ya no se pueden añadir mas conexiones\n");
}

void desplegar_grafo(tiponodo *raiz, int c)
{

  while(c<4)
    {

      if(raiz->dir[c]!=NULL)
	{
	  desplegar_grafo(raiz->dir[c], c);
	}
      if(c == 3)
	{
	  printf("%c->", raiz->dato);
	}
      c++;
    }
}


void buscar_nodo(tiponodo *raiz, int c, char buscado, tiponodo **aux)
{

  if(raiz->dato != buscado)
    {
      while(c<4){

	if(raiz->dir[c]!=NULL)
	  {
	    buscar_nodo(raiz->dir[c], 0, buscado, aux);
	  }
      c++;
      }
    }
  else
    {
      __fpurge(stdin);
      printf("Nodo encontrado\n");
      *aux=raiz;
      getchar();
    }
}



