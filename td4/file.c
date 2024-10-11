// Implanter les files de chaines de caracteres sous forme de liste chainees circulaires.
#include "file.h"

// Crée une file vide
queue_t queue_new(){
    list_t l = list_new();
    if (l == NULL) return NULL;
    // Pour une liste circulaire, lorsque le premier élément est ajouté,
    // son next doit pointer sur lui-même.
    return l;
}

// Retourne VRAI si l est une file vide
int queue_is_empty(queue_t l){
    return list_is_empty(l);
}

// Retourne l'élément en tête de la file
// La queue de la file est pointée par le champ data
// La tete de la file est pointée par le champ data->next
// PRECONDITION : queue non vide
char* queue_first(queue_t l){
    if (queue_is_empty(l)) {
        printf("La file est vide!\n");
        return NULL;
    }
    // l->data pointe sur le dernier maillon
    // le premier maillon est l->data->next
    return l->data->next->data;
}

// Ajoute l'élément e en fin de la file et retourne la nouvelle queue
// Allocation d'un maillon, ajoute ce maillon a la liste circulaire
// dont le dernier maillon est pointé par l->data ....
// Retourne la queue NON MODIFIEE en cas d'erreur
queue_t queue_enqueue(char* e, queue_t l){
    link_t new_link = (link_t)malloc(sizeof(struct _link));
    if (!new_link) return l;
    new_link->data = strdup(e);

    if (!new_link->data) {
        free(new_link);
        return l;
    }
    
    if (queue_is_empty(l)) {
        // La file est vide, le nouveau maillon pointe sur lui-même
        new_link->next = new_link;
        l->data = new_link; // data pointe sur le dernier maillon
    } 
    else {
        // La file n'est pas vide
        new_link->next = l->data->next; // Nouveau maillon pointe sur le premier maillon
        l->data->next = new_link; // Ancien dernier maillon pointe sur le nouveau
        l->data = new_link; // data pointe sur le nouveau dernier maillon
    }
    
    l->size++;
    return l;

}

// Supprime le maillon en tête de file et retourne l'element
// Ne libere PAS l'element, puisqu'il est retourné
// PRECONDITION : queue non vide
char* queue_dequeue(queue_t l ){
    if (queue_is_empty(l)) {
        printf("La file est vide!\n");
        return NULL;
    }
    
    // l->data pointe sur le dernier maillon
    link_t first = l->data->next; // Premier maillon
    char* elem = strdup(first->data); // Dupliquer l'élément à retourner
    if (!elem) return NULL; // Retourner NULL en cas d'erreur de duplication
    
    if (l->data == first) {
        // Il n'y a qu'un seul maillon dans la file
        free(first->data);
        free(first);
        l->data = NULL;
    } 
    else {
        // Il y a plusieurs maillons
        l->data->next = first->next; // Le dernier maillon pointe sur le second maillon
        free(first->data);
        free(first);
    }
    
    l->size--;
    return elem;

}

// Retourne le nombre d'éléments (ou de maillons) de la file
size_t queue_length(queue_t l){
    return list_length(l);
}

// Affiche la file
void queue_printf(queue_t l){
    if (queue_is_empty(l)) {
        printf("File vide.\n");
        return;
    }
    printf("File (tête à gauche): ");
    link_t last = l->data; // Dernier maillon
    link_t current = last->next; // Premier maillon
    for (unsigned int i = 0; i < l->size; i++) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Libère toute la queue et retourne une file vide
// Libère aussi les éléments
queue_t queue_delete(queue_t l){
    if (l == NULL) return NULL;
    while (!queue_is_empty(l)) {
        char* elem = queue_dequeue(l);
        if (elem != NULL) {
            free(elem); // Libérer l'élément retourné par dequeue
        }
    }
    // list_delete libère la structure de la liste
    list_delete(l);
    return NULL;
}

int main(){

    // Créer une nouvelle file
    queue_t q = queue_new();
    
    if (q == NULL) {
        fprintf(stderr, "Erreur: échec de la création de la file.\n");
        return EXIT_FAILURE;
    }

    // Vérifier si la file est vide
    if (queue_is_empty(q)) {
        printf("La file est vide.\n");
    }

    // Enfiler des éléments
    queue_enqueue("Premier", q);
    queue_enqueue("Second", q);
    queue_enqueue("Troisième", q);

    // Afficher la file
    queue_printf(q); // Sortie: Premier Second Troisième 

    // Obtenir le premier élément
    char* first = queue_first(q);
    if (first != NULL) {
        printf("Premier élément de la file: %s\n", first); // Sortie: Premier
    }

    // Défiler un élément
    char* dequeued = queue_dequeue(q);
    if (dequeued != NULL) {
        printf("Élément défiler: %s\n", dequeued); // Sortie: Premier
        free(dequeued); // Libérer la mémoire de l'élément défiler
    }

    // Afficher la file après défiler
    queue_printf(q); // Sortie: Second Troisième 

    // Défiler tous les éléments
    dequeued = queue_dequeue(q);
    if (dequeued != NULL) {
        printf("Élément défiler: %s\n", dequeued); // Sortie: Second
        free(dequeued);
    }

    dequeued = queue_dequeue(q);
    if (dequeued != NULL) {
        printf("Élément défiler: %s\n", dequeued); // Sortie: Troisième
        free(dequeued);
    }

    // Tenter de défiler sur une file vide
    dequeued = queue_dequeue(q); // Devrait afficher une erreur
    if (dequeued != NULL) {
        printf("Élément défiler: %s\n", dequeued);
        free(dequeued);
    }

    // Tenter de regarder le premier élément d'une file vide
    first = queue_first(q); // Devrait retourner NULL
    if (first != NULL) {
        printf("Premier élément de la file: %s\n", first);
    } else {
        printf("La file est vide, aucun premier élément.\n");
    }

    // Afficher la file finale
    queue_printf(q); // Sortie: File vide ou rien

    // Supprimer la file
    q = queue_delete(q);

    return EXIT_SUCCESS;
}