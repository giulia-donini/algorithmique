/* Définir le type abstrait table_double permettant de travailler avec des 
  tableaux de réels dont la dimension sera donnée au clavier. */

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
table_t table_printf(table_t tab){
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
table_t table_append(double val, table_t tab){
  double *tmp = realloc(tab->data, (tab->size + 1) * sizeof(double));
    if (tmp == NULL) {
        return NULL;
    }
    tab->data = tmp;
    tab->data[tab->size] = val;
    tab->size += 1;
}

// fonction d'insertion d'un element en position index dans le tableau
table_t table_insert_at(double val, int index, table_t tab){

  if (index < 0 || index > tab->size) {
      return NULL; 
  }

  // réallouer de la mémoire pour le tableau avec une taille augmentée
  double *tmp = realloc(tab->data, (tab->size + 1)* sizeof(double));
  if (tmp == NULL) {
      return NULL; 
  }

  // déplace les éléments à partir de l'index vers la droite
  if (index < tab->size) {
      memmove(&tmp[index + 1], &tmp[index], (tab->size - index)* sizeof(double));
  }

  tmp[index] = val;

  // mettre à jour le pointeur du tableau et la taille
  tab->data = tmp;
  tab->size += 1;

  return tab; 
}

// fonction de suppression de l'element en position index dans le tableau
table_t table_remove_at(int index, table_t tab){

  if (index < 0 || index > tab->size) {
      return NULL; 
  }

  // déplacez les éléments après l'index vers la gauche
  if (index < tab->size - 1) {
      memmove(&tab->data[index], &tab->data[index + 1], (tab->size - index - 1)* sizeof(double));
  }

  // réduisez la taille du tableau
  double *tmp = realloc(tab->data, (tab->size - 1)* sizeof(double));
  if (tmp == NULL && tab->size > 1) {
      return NULL; 
  }

  // mettre à jour la structure avec le tableau redimensionné et la nouvelle taille
  tab->data = tmp;
  tab->size -= 1;

  return tab; 

}

int main() { 
  int n;
  table_t ptab;

  // creation du tableau
  printf("taille du tableau ? \n"); scanf ("%d",&n);
  ptab= table_new(n);

  // lecture clavier
  printf("écrire les éléments\n");
  for (int i=0; i<ptab->size; i++)
  scanf("%lf", ptab->data+i);
  table_printf(ptab);

  // ajouter des éléments à la fin
  printf("ajout 2 éléments à la fin du tableau\n");
  for (int i = 0; i < 2; i++){
    int x = random() % 100;
    table_append(x, ptab);
  }
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

