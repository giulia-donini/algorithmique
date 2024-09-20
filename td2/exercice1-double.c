// Programmer les différentes fonctions réalisant l'interface de programmation du type vect_t 
// pour des réels double précision, puis pour des chaines de caractères.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vect_t {
  double* data;
  unsigned int max_size;
  unsigned int actual_size;
  }  * vect_t;


// Création d'un tableau de taille initiale n
vect_t vect_new(unsigned int n){

    vect_t vecr;

    // allocation de la structure *IMPORTANT*
    vecr=calloc(1,sizeof(*vecr));

    // Mise a jour des tailles max et actuelle
    vecr->max_size=n;
    vecr->actual_size=0;

    // allocation des données
    if ((vecr->data=calloc(n,sizeof(*(vecr->data))))==NULL) {
        free(vecr);
        return NULL;
    }

    return vecr;
    
}

// Ajout d'un élément en fin de tableau
vect_t vect_append(double e, vect_t table){

    // réallouer de la mémoire pour le tableau avec une taille augmentée si trop petit
    if(table->actual_size == (table->max_size-1)){
        double *tmp = realloc(table->data, (table->max_size*2)* sizeof(double));
        if (tmp == NULL) {
            return NULL; 
        }
        table->max_size = table->max_size * 2;
        table->data = tmp;
    }
    table->data[table->actual_size] = e;
    table->actual_size++;

    return table; 
}

// Suppression des n derniers éléments
vect_t vect_remove_nlast(int n, vect_t table){
    if (n  < 0 || n >= table->actual_size) {
        return NULL; 
    }
    for (int i = 0; i < n; i++){
        table->data[table->actual_size - i - 1] = 0;
    }
    table->actual_size -= n;
    return table; 
}

// Suppression du tableau
vect_t vect_delete(vect_t table){
    free(table->data);
    free(table);
    return NULL;
}

// Affichage du tableau
vect_t vect_print(vect_t table){
  for (int i=0; i<table->actual_size; i++)
    printf("%lf ", *(table->data+i));
  printf("\n");
}

// Insertion d'un élément en position i
vect_t vect_insert_at(double val, int index, vect_t table){

    if (index < 0 || index > table->actual_size) {
        return NULL; 
    }

    // réallouer de la mémoire pour le tableau avec une taille augmentée si trop petit
    if(table->actual_size == (table->max_size-1)){
        double *tmp = realloc(table->data, (table->max_size*2)* sizeof(double));
        if (tmp == NULL) {
            return NULL; 
        }
        table->max_size = table->max_size * 2;
        table->data = tmp;
    }

    // déplace les éléments à partir de l'index vers la droite
    if (index < table->actual_size) {
        for(int j=table->actual_size; j>index;j--){ 
        table->data[j]=table->data[j-1];
        }
    }

    table->actual_size++;
    table->data[index] = val;

    return table; 
}

// Suppression d'un élément en position i
vect_t vect_remove_at(int index, vect_t table){
    if (index < 0 || index > table->actual_size) {
        return NULL; 
    }

    // déplace les éléments à partir de l'index vers la gauche
    if (index < table->actual_size) {
        for(int j=index; j<table->actual_size-1;j++){ 
        table->data[j]=table->data[j+1];
        }
    }

    table->actual_size--;

    return table; 
}


// TEST

int main() { 
    int n;
    vect_t vecr;

    // creation du tableau
    printf("taille du tableau ? \n"); scanf ("%d",&n);
    vecr= vect_new(n);

    // ajouter des éléments à la fin
    printf("ajout des éléments à la fin du tableau\n");
    for (int i = 0; i < n; i++){
        int x = random() % 100;
        vect_append(x, vecr);
    }
    vect_print(vecr);

    // supprimer des derniers éléments
    printf("suppression des 2 derniers éléments\n");
    vect_remove_nlast(2, vecr);
    vect_print(vecr);

    // inserer 1 au index 4
    printf("insertion de 1 au index 4\n");
    vect_insert_at(1,4,vecr);
    vect_print(vecr);

    // supprimer l'élément au index 2
    printf("suppression du élément au index 2\n");
    vect_remove_at(2,vecr);
    vect_print(vecr);

    // supprimer le tableau
    vect_delete(vecr);

    return 0;
}

