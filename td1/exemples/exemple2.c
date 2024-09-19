#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    double* data  ;     // Les données du tableau
    size_t size;    // La taille maximale
} * table_t;

// Fonction allocation de la table
table_t table_new(int n) {
  table_t ptab;

    // Allocation de la structure
  ptab=calloc(1,sizeof(*ptab));
  ptab->size=n;
    // Allocation des données
    if ((ptab->data=calloc(n,sizeof(*(ptab->data))))==NULL) {
      free(ptab);
      return NULL;
    }
  return ptab;
}

int main() { int i;
  table_t ptab;

    // Creation du tableau
  printf("Taille du tableau ? \n"); scanf ("%d",&i);
  ptab= table_new(i);
    // Lecture clavier
  for ( i=0; i<ptab->size; i++)
    scanf("%lf", ptab->data+i);

    void table_print(table_t ptab);

    // Ajout aléatoire
  for ( i=0; i<ptab->size; i++)
    ptab->data[i] += random();

  // Libération du tableau
  free(ptab->data);
  free(ptab);
}
