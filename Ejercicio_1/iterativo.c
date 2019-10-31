#include <stdio.h>
#include <time.h>

//double FibIter(int iteracion);

int main (void)
{
  clock_t start = clock();
  double time = 0.0;
  FILE *Archivo;
  double acumulador[30];
  int i;
  double num1=0.0, num2=1.0, resultado=1.0;
  
  Archivo = fopen("iteracion.txt", "wt");

  for(i=0; i<40; i++)
    {
      printf("%lf\n", resultado);
      resultado = num1 + num2;
      num1 = num2;
      num2 = resultado;
      fprintf(Archivo,"%d, ",i+1);
      clock_t end = clock();
      time = (double)(end-start)/CLOCKS_PER_SEC;
      fprintf(Archivo,"%lf\n",time);
    }
  fclose(Archivo);
}

  

 
