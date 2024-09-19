#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    double* data  ;     // les données du tableau
    size_t size;    // la taille maximale
} * table_t;

// fonction de création d'un tableau de n éléments
table_t table_new(int n) {
  table_t tab;

    // allocation de la structure
  tab=calloc(1,sizeof(*tab));
  tab->size=n;
    // allocation des données
    if ((tab->data=calloc(n,sizeof(*(tab->data))))==NULL) {
      free(tab);
      return NULL;
    }
  return tab;
}

// fonction de suppression du tableau
table_t table_delete(table_t tab){
  free(tab->data);
  free(tab);
  return NULL;
}

// fonction d'affichage du tableau
void table_printf(table_t tab){
  for (int i=0; i<tab->size; i++)
    printf("%lf ", *(tab->data+i));
  printf("\n");
}

// fonction de minimum du tableau
double table_min(table_t tab){

    double min = tab->data[0];  // supposer que le premier élément est le minimum

    for (int i = 1; i < tab->size; i++) {
        if (tab->data[i] < min) {
            min = tab->data[i];  // trouver un nouveau minimum
        }
    }
    return min;
}

// fonction d'ajout d'un element en fin de tableau
int table_append(double val, table_t tab){
  double *new_array = realloc(tab->data, (tab->size + 1) * sizeof(double));
    if (new_array == NULL) {
        return -1;
    }
    tab->data = new_array;
    tab->data[tab->size] = val;
    tab->size += 1;

    return 0;
}

// fonction d'insertion d'un element en position index dans le tableau
int table_insert_at(double val, int index, table_t tab){

    if (index < 0 || index > tab->size) {
        return -1; 
    }

    // réallouer de la mémoire pour le tableau avec une taille augmentée
    double *new_array = realloc(tab->data, (tab->size + 1)* sizeof(double));
    if (new_array == NULL) {
        return -2; 
    }

    // déplace les éléments à partir de l'index vers la droite
    if (index < tab->size) {
        memmove(&new_array[index + 1], &new_array[index], (tab->size - index)* sizeof(double));
    }

    new_array[index] = val;

    // mettre à jour le pointeur du tableau et la taille
    tab->data = new_array;
    tab->size += 1;

    return 0; 
}

// fonction de suppression de l'element en position index dans le tableau
int table_remove_at(int index, table_t tab){
    if (index < 0 || index >= tab->size) {
        return -1; 
    }

    // déplacez les éléments après l'index vers la gauche
    if (index < tab->size - 1) {
        memmove(&tab->data[index], &tab->data[index + 1], (tab->size - index - 1)* sizeof(double));
    }

    // réduisez la taille du tableau
    double *new_array = realloc(tab->data, (tab->size - 1)* sizeof(double));
    if (new_array == NULL && tab->size > 1) {
        return -2; 
    }

    // mettre à jour la structure avec le tableau redimensionné et la nouvelle taille
    tab->data = new_array;
    tab->size -= 1;

    return 0; 
}

int main() { int i;
  table_t ptab;

  // creation du tableau
  printf("taille du tableau ? \n"); scanf ("%d",&i);
  ptab= table_new(i);

  // lecture clavier
  for ( i=0; i<ptab->size; i++)
  scanf("%lf", ptab->data+i);
  table_printf(ptab);

  // ajouter un élément à la fin
  printf("ajout d'un élément (valeur 10.5) à la fin du tableau\n");
  table_append(10.5, ptab);
  table_printf(ptab);

  // insérer un élément
  printf("insertion d'un élément (valeur 20.5) à l'index 2\n");
  table_insert_at(20.5, 2, ptab);
  table_printf(ptab);

  // Supprimer un élément
  printf("suppression de l'élément à l'index 1\n");
  table_remove_at(1, ptab);
  table_printf(ptab);

  // afficher le minimum
  printf("valeur minimale du tableau : %lf\n", table_min(ptab));

  // supprimer le tableau
  table_delete(ptab);

  return 0;
}

