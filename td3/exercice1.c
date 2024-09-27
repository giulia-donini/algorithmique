#include "list.h"

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
    return l == NULL;
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

int main(){
    list_t list;

    if(list_is_empty(list)) printf("the list is empty\n");

    printf("adding 'c' as first element\n");
    list_add_first("c", list);
    printf("%s \n", list_first(list));
    if(!list_is_empty(list)) printf("the list is not empty\n");

    printf("adding 'd' and 'e' as first elements\n");
    list_add_first("d", list);
    list_add_first("e", list);
    list_printf(list);

    printf("deleting first element\n");
    list_del_first(list);
    list_printf(list);

}