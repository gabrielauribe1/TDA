#include <stdio.h>
#include <string.h>
#include <stdlib.h>
    
//funciones del programa
    
void ReducirBits(char *argv[],int contagrc,int *numero);
void GuardarDatos(int contagrc, int numero, int array[4]);
void Imprimir(int contagrc, int array[]);
void ResolverOperaciones(int contagrc, int array[]);
    
int main(int argc, char *argv[])
{
  int contagrc, numero=0, opcmenu, array[4];
  contagrc=argc-1; // se le resta 1 debido al argumento para compilar (./ejercicio2.exe)
    
  if (argc > 5 || argc == 1)
    {
      printf("Debe de introducir los parámetros adecuados en la terminal. \n");
      exit(1);
    }
  else
    {
      ReducirBits(argv, contagrc, &numero);
      GuardarDatos(contagrc, numero, array);
    }
    
  do
    {
      system("clear");
      printf("¡Los números han sido comprimidos de manera exitosa! \n");
      printf("Bienvenido al menú\n\n");
      printf("Intrduzca la opción con la que desea proceder:\n");
      printf("1. Imprimir los números introducidos para comprobar que se guardaron de manera correcta\n2. Resolver operaciones básicas (+, -, *, /) con los números introducidos\n3. Salir del programa\n");
      scanf("%d", &opcmenu);
        
      switch(opcmenu)
	{
	case 1:
	  Imprimir(contagrc, array);
	  break;
	case 2:
	  ResolverOperaciones(contagrc, array);
	  break;
	case 3:
	  printf("El programa ha finalizado.\n");
	  exit(1);
	  break;
	default:
	  printf("Introduzca una opción válida del menú.\n");
	}
      printf("Presione cualquier tecla para continuar.\n");
      __fpurge(stdin);
      getchar();
    }while(opcmenu != 3);
    }
        
void ReducirBits(char *argv[],int contagrc,int *numero)
{
  int temporal, bit=12, i; //se posisiona la variable bit en 12 para que el primer numero se posicione en los primeros 4 bits del int
            
  for(i=0; i<contagrc; i++)
    {
      sscanf(argv[i+1], "%d", &temporal);
	if((strcmp(argv[i+1],"0")==0) || (temporal>=1 && temporal<=15))
	  {
	    temporal <<= bit; //se utiliza bitwise para comprimir los bits
	    *(numero)|= temporal;
	    bit = bit - 4; //cada vez que se entra al ciclo se restan 4 "bits" para que cada número se posicione cada 4 bits
	  }
	else
	  {
	    printf("Programa diseñado para introducir valores del 0 al 15.\n");
	    printf("El programa ha finalizado.\n");
	    exit(1);
	  }
    }
}
        
void GuardarDatos(int contagrc, int numero, int array[]) //esta funcion es la encargada de guardar los datos en un arreglo para poderse imprimir o utilizarse en las operaciones
{
  int temporal, bit=12, i;
            
  for (i=0; i<contagrc; i++)
    {
                
      if(i==0)
	{
	  temporal=numero;
	  array[i] = temporal >> bit;
	}
      else
	{
	  temporal = array[i-1] << bit;
	  numero = numero ^ temporal;
	  temporal = numero;
	  bit = bit - 4;
	  array[i]=temporal>>bit; //durante el ciclo se recorre el entero con los bits guardados y se guardan los números en el arreglo
	}
    }
}
        
void Imprimir(int contagrc, int array[])
{
  int i;

  for(i=0; i<contagrc; i++)
    printf("El número %d es: %d\n", i+1 , array[i]);
}

void ResolverOperaciones(int contagrc, int array[])
{
  int opcmenu, i, j, k, l;
  float res = array[0];

  printf("Introduzca la opcion de la operacion que desea hacer\n");
  printf("1.Suma\n2.Resta\n3.Multiplicación\n4.División\n");
  scanf("%d",&opcmenu);
  switch(opcmenu)
    {
    case 1:
      for(i= 1; i<contagrc; i++)
	res = res + array[i];
      printf("Resultado de la suma: %.2f\n", res);
      break;
    case 2:
      for(j= 1; j<contagrc; j++)
	res = res - array[j];
      printf("Resultado de la resta: %.2f\n", res);
      break;
    case 3:
      for(k= 1; k<contagrc; k++)
	res = res * array[k];
      printf("Resultado de la multiplicación: %.2f\n", res);
      break;
    case 4:
      for(l= 1; l<contagrc; l++)
	res = res / array[l];
      printf("Resultado de la división: %.2f\n", res);
      break;
    default:
      printf("Introduzca una opcion válida\n");
      break;
    }  
}

