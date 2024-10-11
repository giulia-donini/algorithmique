#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vect_t {
  char** data;
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
vect_t vect_append(char* c, vect_t table){

    // réallouer de la mémoire pour le tableau avec une taille augmentée si trop petit
    if(table->actual_size == (table->max_size-1)){
        char** tmp = realloc(table->data, (table->max_size*2)* sizeof(char*));
        if (tmp == NULL) {
            return NULL; 
        }
        table->max_size = table->max_size * 2;
        table->data = tmp;
    }
    table->data[table->actual_size] = strdup(c);
    table->actual_size++;

    return table; 
}

// Suppression des n derniers éléments
vect_t vect_remove_nlast(int n, vect_t table){
    if (n  < 0 || n >= table->actual_size) {
        return NULL; 
    }
    for (int i = 0; i < n; i++){
        table->data[table->actual_size - i - 1] = NULL;
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
void vect_print(vect_t table){
  for (int i=0; i<table->actual_size; i++)
    printf("%s ", *(table->data+i));
  printf("\n");
}

// Insertion d'un élément en position i
vect_t vect_insert_at(char* str, int index, vect_t table){

    if (index < 0 || index > table->actual_size) {
        return NULL; 
    }

    // réallouer de la mémoire pour le tableau avec une taille augmentée si trop petit
    if(table->actual_size == (table->max_size-1)){
        char** tmp = realloc(table->data, (table->max_size*2)* sizeof(char*));
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
    table->data[index] = str;

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