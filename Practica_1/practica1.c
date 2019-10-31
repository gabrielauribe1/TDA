#include <stdio.h>
#include <time.h>

double f(double x, double y);

int main (void)
{
  int i;
  double y, xi, yi, xf, h;

  printf("Introduzca 'y' inicial:\n");
  scanf("%lf", &yi);
  printf("Introduzca 'x' inicial:\n");
  scanf("%lf", &xi);
  printf("Introduzca 'x'  final:\n");
  scanf("%lf", &xf);
  printf("Introduzca el tamaño 'h':\n");
  scanf("%lf", &h);
  printf("x\t\ty\t\ty'\t\thy'\t\ty+hy'\n");
  printf("___________________________________________________________\n");

  while(xi<xf)
    {
      y=yi+h*(xi, yi);
      printf("%lf\t%lf\t%lf\t%lf\t%lf\n", xi, yi, f(xi, yi), h*f(xi, yi), y);
      yi=y;
      xi=xi+h;
    }
  printf("%lf\t%lf\n", xi, yi);
  printf("El valor de y es %lf \n", y);
  
}

double f(double x, double y)
{
  return -2*x-y;
}
