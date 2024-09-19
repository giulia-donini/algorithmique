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


table_t table_new(int n, void* (*delete_data)(void*), int (*equal_data)(void*,void*), void (*fprint_data)(void*, FILE*)) { 
  int i;
  table_t ptab;

    // Allocation de la structure
  if ( (ptab=malloc(sizeof(*ptab))) ==NULL)
    return NULL;

    // Mise a jour des tailles max et actuelle
  ptab->max_size=n;
  ptab->actual_size=0;
  ptab->delete_data=delete_data;
  ptab->equal_data=equal_data;
  ptab->fprint_data=fprint_data;

    // Allocation des données
  if ( (ptab->data=calloc(n,sizeof(*(ptab->data)))) ==NULL) {
    free(ptab);
    return NULL;
  }
    // Fin creation et retour
  return ptab;
}

table_t table_append(void* e, table_t tab) {
  if (tab==NULL) return NULL;
  tab->data[tab->actual_size]=e;
  tab->actual_size++;
  return tab;
}

table_t table_delete(table_t tab) { int i;
  if (tab==NULL) return NULL;
    // A t on passe une fonction de liberation des elements ?
  if (tab->delete_data)
      // On libere les elements grace à notre pointeur
    for (i=0; i<tab->actual_size; i++)
      tab->delete_data(tab->data[i]);

    // On libere le tableau et la structure allouée
  free(tab->data);
  free(tab);
  return NULL;
}

void table_fprint(table_t table, FILE *fp) {
    if (table==NULL) return;
    double* px;
    for(int i=0;i<table->actual_size; i++){
      px=(double*)table->data[i];
      fprintf(fp,"%.2lf ",*px);
    }
}

void table_print(table_t table) {
    table_fprint(table,stdout);
    printf("\n");
}

table_t table_insertat(int i, void *e, table_t table) {
    if (table==NULL) return NULL;
    if (i < 0 && i >= table->actual_size) return NULL;
    table->data[i]=e;
    return table;
}

table_t table_removeat(table_t table, int i) {
    if (table==NULL) return NULL;
    if (i < 0 && i >= table->actual_size) return NULL;
    for(int j=i; j<table->actual_size-1;j++){ 
      table->data[j]=table->data[j+1];
    }
    table->actual_size--;
    return table;
}



int main() { 
  
  int size = 10;
  double* px;
  // tab sera un tableau de 10 réels double
  table_t tab;

  // Creation du tableau
  tab=table_new(size,NULL,NULL,NULL);

  // Ajout de 5 elements aléatoires
  for( int i=0; i<size; i++)  {
    // Creation d'un reel
    px= malloc(sizeof(*px));
    *px = random() % 100;
      // Ajout du reel à la fin et mise a jour de la taille
  printf("Ajoutant %.2lf au tableau\n", *px);
  tab = table_append(px, tab);
  }

  table_print(tab);
  puts("");

  // Libération du tableau ET des éléments
  tab=table_delete(tab);
  // Ici, la mémoire est libérée correctement
}