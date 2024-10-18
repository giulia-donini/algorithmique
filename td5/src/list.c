#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _link {
  char* data;               /* un élément de la liste*/
  struct _link *next;       /* l'adresse du maillon suivant */
} *link_t;

typedef struct _list{
  link_t data;              /* la tête de la liste */
  unsigned int size;        /* nombre de maillons */
} * list_t;

// Creation d'une liste vide
list_t list_new(){

    list_t l;

    // allocation de la structure *IMPORTANT*
    //l=calloc(1,sizeof(*l));

    l = (list_t)malloc(sizeof(struct _list));
    if (!l) return NULL;

    l->data = NULL;
    l->size = 0;

    return l;
}

// Retourne VRAI si l est une liste vide
int list_is_empty(list_t l){
    return l->size == 0;
}

// Retourne VRAI si l est un maillon vide
int link_is_empty(link_t l){
    return l->data == NULL;
}

// Retourne l'élément en tête de liste : PRECONDITION : liste non vide
char* list_first(list_t l){
    if (list_is_empty(l)) return NULL;
    return l->data->data;
}

// Ajoute l'élément e en tête des maillons et retourne cette tete
// Retourne la tete NON MODIFIEE en cas d'erreur
link_t link_add_first(char* c, link_t l){
    link_t new_link = (link_t)malloc(sizeof(struct _link));
    if (!new_link) return l;
    new_link->data = strdup(c);  // Copie la chaîne
    new_link->next = l;
    return new_link;
}

// Ajoute l'élément e en tête de liste et retourne cette liste
list_t list_add_first(char* c, list_t l){
    l->data = link_add_first(c, l->data);
    l->size++;
    return l;
}

// Supprime le maillon en tête des maillons et retourne les maillons
// PRECONDITION : maillons non vide
link_t link_del_first(link_t l){
    if (link_is_empty(l)) return NULL;
    link_t temp = l;
    l = l->next;
    free(temp->data);
    free(temp);
    return l;
}

// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
list_t list_del_first(list_t l ){
    if (list_is_empty(l)) return l;
    l->data = link_del_first(l->data);
    l->size--;
    return l;
}

// Retourne le nombre d'éléments (ou de maillons) de la liste
size_t list_length(list_t l){
    return l->size;
}

// Affiche la liste a l'ecran, dans un fichier.
void list_fprintf(list_t l, FILE* fp){
    link_t current = l->data;
    for (int i = 0; i < l->size; i++) {
        fprintf(fp, "%s\n", current->data);
        current = current->next;
    }
}

void list_printf(list_t l){
    list_fprintf(l, stdout);
}

// Libère toute la liste et retourne une liste vide
list_t list_delete(list_t l){
     while (!list_is_empty(l)) {
        l = list_del_first(l);
    }
    return l;
}

// Ajoute en queue de liste, eventuellement
link_t link_add_last(char* c, link_t l){
    link_t new_link = (link_t)malloc(sizeof(struct _link));
    if (!new_link) return l;
    new_link->data = strdup(c);
    new_link->next = NULL;
    if (link_is_empty(l)) return new_link;

    link_t current = l;
    while (current->next != NULL){
        current = current->next;
    }
    current->next = new_link;
    return l;
}

list_t list_add_last(char* c, list_t l){
    l->data = link_add_last(c, l->data);
    l->size++;
    return l;
}

//Suppression en queue, eventuellement
link_t link_del_last(link_t l){
    if (link_is_empty(l)) return NULL;

    if (l->next == NULL) {
        free(l->data);
        free(l);
        return NULL;
    }

    link_t current = l;
    while (current->next != NULL){
        current = current->next;
    }
    free(current->data);
    free(current);
    return l;
}

list_t list_del_last(list_t l ){
    if (list_is_empty(l)) return l;
    l->data = link_del_last(l->data);
    l->size--;
    return l;
}

int compare_strings(char* c1, char* c2) {
    return strcmp(c1, c2);
}

// Recherche un element selon le critere compare. Retourne le maillon trouve ou NULL
link_t list_lookup(char* elem, list_t l, int(*compare)(char* c1, char* c2)) {
    link_t current = l->data;

    while (current != NULL) {
        if (compare(current->data, elem) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Recherche le premier maillon contenant e,
// au sens du equal_data ou de l'egalite de pointeurs si equal_data est NULL
// ou NULL si e n'est pas dans la liste       
link_t list_find(char* c, list_t l){
    link_t current = l->data;  // Commence par le premier maillon

    // Traverse the list
    while (current != NULL) {
        // Compare les chaînes avec strcmp
        if (strcmp(current->data, c) == 0) {
            return current;  // Element trouvé
        }
        current = current->next;  // Passe au maillon suivant
    }

    return NULL;  // Retourne NULL si l'élément n'est pas trouvé
}

// Suppression de l'element param, au sens de equal_data
list_t list_remove(char* param, list_t l){
    if (list_is_empty(l)) return l;  // Si la liste est vide, rien à supprimer

    link_t to_remove = list_find(param, l);  // Trouve le maillon contenant `param`
    if (to_remove == NULL) return l;  // L'élément n'est pas trouvé, pas de suppression

    link_t current = l->data;
    link_t prev = NULL;

    // Recherche du maillon à supprimer (celui trouvé par list_find)
    while (current != NULL) {
        if (current == to_remove) {
            // Si le maillon à supprimer est trouvé
            if (prev == NULL) {
                // Si le maillon est en tête de la liste
                l->data = current->next;
            } else {
                // Si le maillon est au milieu ou en fin
                prev->next = current->next;
            }

            // Libération de la mémoire du maillon à supprimer
            free(current->data);
            free(current);
            l->size--;  // Mise à jour de la taille de la liste
            return l;
        }

        // Passage au maillon suivant
        prev = current;
        current = current->next;
    }

    return l;  // Retourne la liste après suppression
}


