#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    void* * data  ;         // Les données du tableau : un pointeur vers des pointeurs
    size_t max_size;      // La taille maximale
    size_t actual_size;    // La taille actuelle

    void* (*delete_data)(void*); // Un pointeur vers la fonction qui libère les éléments
    int (*equal_data)(void*,void*); // Comment tester l'egalite de 2 elements
    void (*fprint_data)(void*, FILE*); // Comment afficher un éléments
} * table_t;

table_t table_new(int n, void* (*delete_data)(void*)) { int i;
  table_t ptab;

    // Allocation de la structure
  if ( (ptab=malloc(sizeof(*ptab))) ==NULL)
    return NULL;

    // Mise a jour des tailles max et actuelle
  ptab->max_size=n;
  ptab->actual_size=0;
  ptab->delete_data=delete_data;

    // Allocation des données
  if ( (ptab->data=calloc(n,sizeof(*(ptab->data)))) ==NULL) {
    free(ptab);
    return NULL;
  }
    // Fin creation et retour
  return ptab;
}

int main() { int i;
  double* px;
    // tab sera un tableau de 10 réels double
  table_t tab;

    // Creation du tableau
  tab=table_new(10,NULL);

    // Ajout de 5 elements aléatoires
  for( i=0; i<5; i++)  {
      // Creation d'un reel
    px= malloc(sizeof(*px));
    *px = random() % 100;
      // Ajout du reel à la fin et mise a jour de la taille
    tab->data[tab->actual_size++]=px;
  }

    // affichage des éléments ajoutés
  for ( i=0; i<tab->actual_size; i++)  {
      // On recupere le pointeur sur un reel : conversion explicite obligatoire pour utiliser l'element
    px= (double*) tab->data[i];
      // Affichage du reel
    printf("%lf ",*px);
  }
  puts("");
}