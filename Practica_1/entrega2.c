#include<stdio.h>
#include<math.h>

void euler(float x0,float xn,float y0,float h,float formula[],float xy[2][30],int *max);
float resolver(float x,float formula[]);

int main(void){
  float x0,xn,y0,h,formula[10]={0},xy[2][30];
  int exponente,i,max=0;
  FILE *archivo;
  printf("Introduzca el valor de x0\n");
  scanf("%f",&x0);
  printf("Introduzca el valor de xn\n");
  scanf("%f",&xn);
  printf("Introduzca el valor de y0\n");
  scanf("%f",&y0);
  printf("Introduzca el valor de h\n");
  scanf("%f",&h);
  printf("Cual es el exponente mayor?\n");
  scanf("%i",&exponente);
  for(i=exponente;i>=0;i--){
    printf("Introduzco el valor de x con exponente %i\n",i);
    scanf("%f",&formula[i]);
  }
  printf("Calculando euler\n");
  euler(x0,xn,y0,h,formula,xy,&max);
  archivo=fopen("Euler.txt","wt");
  for(i=0;i<max;i++)
    fprintf(archivo,"%.2f   %.2f\n",xy[0][i],xy[1][i]);
  fclose(archivo);
}

void euler(float x0,float xn,float y0,float h,float formula[],float xy[2][30],int *max){
  float x;
  int i=0;
  //coloca en la primeras coordenadas x0 y y0
  xy[0][0]=x0;
  xy[1][0]=y0;
  //calcula los numeros de Euler
  while(x0<=xn){
    x=xy[0][0]+(double)i*h;//resuleve x para la resolucion de la formula
    xy[0][i+1]=xy[0][i]+h;//aumenta en h la coordenada x
    xy[1][i+1]=xy[1][i]+resolver(x,formula)*h;//calcula la coordenada y
    i++;
    (*max)++;//Para imprimir nada mas los numeros que se resolvieron
    x0+=h;
  }
}

float resolver(float x,float formula[]){//resuelve la formula con la x dada
  int i=9;
  float suma[10],j=0;
  while(i>=0){
    suma[i]=formula[i]*pow(x,i);
    j+=suma[i];
    i--;
  }
  return j;
}
