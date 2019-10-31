#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct def_Fourier
{
  double Amp, Frec, Tf, *mtime, *resolver;
  double Harm, Mt;
} TipoFourier;

void Datos(TipoFourier *inicio);
double ResFunc(TipoFourier inicio, double Ti);
void Decodificar(TipoFourier inicio, double Ti);
void Archivo(TipoFourier inicio);
void Graficar();


int main (void)
{
  TipoFourier Inicio;
  double Ti;

  Datos(&Inicio);
  Inicio.mtime = (double *) malloc (sizeof(TipoFourier)*Inicio.Mt);
  Inicio.resolver = (double *) malloc (sizeof(TipoFourier)*Inicio.Mt);
  ResFunc(Inicio, Ti);
  Decodificar(Inicio, Ti);
  Archivo(Inicio);
  Graficar();

  return 0;
}


/*  *Funcion encardada de pedir los datos necesarios al usuario
    *@param TipoFourier inicio, se le pasa el parametro de la estructura para ir guardando cada dato en cada elemento indicado de la estructura
*/
void Datos(TipoFourier *inicio) 
{
  printf("Introduzca los datos necesarios:\n");
  printf("Amplitud:\n");
  scanf(" %lf", &inicio->Amp);
  printf("Frecuencia:\n");
  scanf(" %lf", &inicio->Frec);
  printf("Harmonico:\n");
  scanf(" %lf", &inicio->Harm);
  printf("Tiempo Final:\n");
  scanf(" %lf", &inicio->Tf);
  printf("Muster Tiempo:\n");
  scanf(" %lf", &inicio->Mt);
}


/*  *Funcion encardada de resolver la funcion con los valores obtenidos por el usuario, se sustituyen los valores en la fomula. El valor de Ti es obtenido en la funcion de decodificar
    *@param TipoFourier inicio, se utilizan los elementos guardados en la estructura
    *@param double Ti, se declara como double para que la multiplicacion en la formula sea toda del mismo valor 
*/

double ResFunc(TipoFourier inicio, double Ti)
{
  double Resultado=0;
  int i;
  float pip=3.14159;

  for(i=1; i<inicio.Harm; i++) //inicia en 1, para que no se divida entre 0, y termina al final del harmonico
    {
      Resultado += (inicio.Amp/(pip*i)*(cos(pip*i)-1)*(sin(2*pip*inicio.Frec*Ti*i))); //fórmula aplicada del documento del profesor
    }
  return Resultado; //me regresa el resultado
}


/*  *Funcion encargada de decodificar la señal
    *@param TipoFourier inicio, se utilizan los elementos guardados en la estructura
    *@param double Ti, se refiere al tiempo inicial (0), se declara como double para que la division(delta f) al ir incrementando en el for sea del mismo valor
*/

void Decodificar(TipoFourier inicio, double Ti)
{
  int i=0;
  
  for(Ti=0; Ti<= inicio.Tf; Ti+=(inicio.Tf/inicio.Mt))//inicia Ti en 0, termina al final del tiemo, va incrementando con delta f
    {
      inicio.mtime[i] = Ti; //coordenada x (muster time)
      inicio.resolver[i] = inicio.Amp/2 - ResFunc(inicio, Ti); //coordenada y (señal)
      i++;
    }
}


/*  *Funcion encargada de imprimir las coordenadas de muster time(x) y las coordenadas de la señal(y)
    *@param TipoFourier inicio, se utilizan los elementos guardados en la estructura
*/
void Archivo(TipoFourier inicio)
{
  int i;
  FILE *Archivo;
  
  Archivo = fopen("Fourier3.txt","wt");

  for(i=0; i<inicio.Mt; i++)// inicia en 0, hasta el muster time para desplazar los datos del archivo de manera correcta
    {
      fprintf(Archivo,"%lf %lf \n", inicio.mtime[i], inicio.resolver[i]); //imprime dentro del archivo Fourier.txt las coordenadas x y las coordenadas y
    }
  
  fclose(Archivo);
}

/*  *Funcion encargada de desplegar la grafica con los datos obtenidos anteriormente, guardados en el archivo Fourier.txt
*/

void Graficar() 
{
  int i;
  char *AbrirGnuPlot[] = {"set title \"Serie de Fourier\"",
			  "set ylabel \"----Señal--->\"",
			  "set xlabel \"----Muster Time--->\"",
			  "plot \"Fourier3.txt\" with lines"
  };
  FILE *VentanaGnuPlot = popen ("gnuplot -persist", "w");
  for (i=0; i<4; i++)
    fprintf(VentanaGnuPlot, "%s \n", AbrirGnuPlot[i]);
}

