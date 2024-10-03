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


// Les visiteurs
void list_simple_visit(list_t l, void (*exec_on_value)(void*, void*), void* param) {
    if (list_is_empty(l)) return;  // Si la liste est vide, rien à faire

    link_t current = l->data;
    while (current != NULL) {
        exec_on_value(current->data, param);  // Applique la fonction à chaque élément
        current = current->next;
    }
}

void list_visit(list_t l, int (*exec_on_value)(void*, void*), int (*exec_on_link)(list_t, void*), void* param) {
    if (list_is_empty(l)) return;  // Si la liste est vide, rien à faire

    link_t current = l->data;
    while (current != NULL) {
        // Exécution sur la valeur (si exec_on_value est fourni)
        if (exec_on_value && exec_on_value(current->data, param) != 0) {
            break;  // Si la fonction retourne non zéro, on arrête le parcours
        }

        // Exécution sur le maillon (si exec_on_link est fourni)
        if (exec_on_link && exec_on_link(l, param) != 0) {
            break;  // Si la fonction retourne non zéro, on arrête le parcours
        }

        current = current->next;
    }
}


int main(){
    list_t list = list_new();;

    if(list_is_empty(list)) printf("the list is empty\n");

    printf("\nadding 'c' as first element\n");
    list_add_first("c", list);
    printf("%s \n", list_first(list));
    if(!list_is_empty(list)) printf("\nthe list is not empty\n");

    printf("\nadding 'd' and 'e' as first elements\n");
    list_add_first("d", list);
    list_add_first("e", list);
    list_printf(list);

    printf("\ndeleting first element\n");
    list_del_first(list);
    list_printf(list);

    printf("\nadding and removing b as last element\n");
    list_add_last("b", list);
    list_printf(list);
    printf("\n");
    list_del_last(list);
    list_printf(list);

    
    char* search_elem = "d";
    link_t found_link = list_lookup(search_elem, list, compare_strings);

    if (found_link != NULL) {
        printf("element '%s' found!\n", found_link->data);
    } else {
        printf("element '%s' not found.\n", search_elem);
    }

    printf("\nremoving d\n");
    list_remove(search_elem, list);
    list_printf(list);
}