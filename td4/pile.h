#ifndef _pile_H
#define _pile_H
#include <assert.h>
#include "src/tabredim.c"

// Une pile est un tableau redimensionnable
typedef vect_t  stacks_t;

// Creation d'une pile de n elements
stacks_t stacks_new(unsigned int n);

// Empiler un element
stacks_t stacks_push(char* e, stacks_t table);

// Depile un element en le retournant, supprime l'element de la pile
char* stacks_pop(stacks_t table);

// Retourne le premier element, sans le supprimer
char* stacks_peek(stacks_t table);

// Pile vide ?
int stacks_is_empty(stacks_t l);

// Affiche la pile
void stacks_printf(stacks_t table);
void stacks_fprintf( stacks_t table,FILE*);

// Supprime la pile
stacks_t stacks_delete(stacks_t table);
#endif
