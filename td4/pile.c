// Implanter les piles de chaines de caractères sous forme de tableau redimensionnable
#include "pile.h"

// Creation d'une pile de n elements
stacks_t stacks_new(unsigned int n){
    return vect_new(n);
}

// Empiler un element
stacks_t stacks_push(char* e, stacks_t table){
    return vect_append(e, table);
}

// Depile un element en le retournant, supprime l'element de la pile
char* stacks_pop(stacks_t table){
    if(stacks_is_empty(table)){
        fprintf(stderr, "Erreur: tentative de dépilement d'une pile vide.\n");
        return NULL;
    }  
    table->actual_size--;
    char* elem = table->data[table->actual_size];
    table->data[table->actual_size] = NULL;
    return elem; // Retourne l'élément dépilé
}

// Retourne le premier element, sans le supprimer
char* stacks_peek(stacks_t table){
    if(stacks_is_empty(table)){
        fprintf(stderr, "Erreur: tentative de peek sur une pile vide.\n");
        return NULL;
    }
    return table->data[table->actual_size - 1];
}

// Pile vide ?
int stacks_is_empty(stacks_t l){
    return (l->actual_size == 0);
}

// Affiche la pile
void stacks_printf(stacks_t table){
    printf("Pile (sommet à droite): ");
    vect_print(table);
}
void stacks_fprintf( stacks_t table,FILE* f){
    fprintf(f, "Pile (sommet à droite): ");
    for(unsigned int i = 0; i < table->actual_size; i++){
        fprintf(f, "%s ", table->data[i]);
    }
    fprintf(f, "\n");
}

// Supprime la pile
stacks_t stacks_delete(stacks_t table){
    return vect_delete(table);
}

int main(){
    // Créer une nouvelle pile avec une capacité initiale de 2
    stacks_t pile = stacks_new(2);

    // Empiler des éléments
    pile = stacks_push("Premier", pile);
    pile = stacks_push("Second", pile);
    pile = stacks_push("Troisième", pile); // La pile se redimensionne automatiquement

    // Afficher la pile
    stacks_printf(pile); // Sortie: Premier Second Troisième 

    // Voir le sommet de la pile
    char* sommet = stacks_peek(pile);
    if(sommet != NULL){
        printf("Sommet de la pile: %s\n", sommet); // Sortie: Sommet de la pile: Troisième
    }

    // Dépiler un élément
    char* depile = stacks_pop(pile);
    if(depile != NULL){
        printf("Élément dépilé: %s\n", depile); // Sortie: Élément dépilé: Troisième
        free(depile); // N'oubliez pas de libérer la mémoire de l'élément dépilé
    }

    // Afficher la pile après dépilement
    stacks_printf(pile); // Sortie: Premier Second 

    // Supprimer la pile
    pile = stacks_delete(pile);

    return 0;
}