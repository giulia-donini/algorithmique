#include <stdio.h>
#include <stdlib.h>
#define DIM 10

int main() {
  double tab[DIM];
  int i;

  for ( i=0; i<DIM; i++)
    scanf("%lf", tab+i);
  for ( i=0; i<DIM; i++)
    tab[i] += random();
  printf("%f",tab[4]);
}
