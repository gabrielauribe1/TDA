#include <stdio.h>
#include <time.h>

double FibRec(int iteracion);

int main (void)
{
  clock_t end = clock();
  double time = 0.0;
  FILE *Archivo;
  double acumulador[30];
  clock_t start = clock();
  int i;

  Archivo = fopen("recursion.txt", "wt");

  for(i=0;i<40; i++)
    {
      start = clock();
      FibRec(i);
      end = clock();
      time = (double)(end-start) /CLOCKS_PER_SEC;
      acumulador[i]= time;
      fprintf(Archivo, "%d\t", i+1);
      fprintf(Archivo, "%lf\n", time);
    }
  
  fclose(Archivo);
}

double FibRec (int iteracion)
{
  if (iteracion == 0 || iteracion == 1)
    return iteracion;
  else
    return FibRec (iteracion -1) + FibRec (iteracion-2);
}
