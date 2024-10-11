#ifndef _QUEUE_H
#define _QUEUE_H
/// Il faut utiliser les listes génériques
#include "src/list.c"

/// Une queue est une liste générique circulaire
/// Attention, la liste est circulaire, le champ data
/// doit pointé sur le dernier élément de la liste
typedef list_t queue_t;

// Crée une file vide
queue_t queue_new();

// Retourne VRAI si l est une file vide
int queue_is_empty(queue_t l);

// Retourne l'élément en tête de la file
// La queue de la file est pointée par le champ data
// La tete de la file est pointée par le champ data->next
// PRECONDITION : queue non vide
char* queue_first(queue_t l);

// Ajoute l'élément e en fin de la file et retourne la nouvelle queue
// Allocation d'un maillon, ajoute ce maillon a la liste circulaire
// dont le dernier maillon est pointé par l->data ....
// Retourne la queue NON MODIFIEE en cas d'erreur
queue_t queue_enqueue(char* e, queue_t l);

// Supprime le maillon en tête de file et retourne l'element
// Ne libere PAS l'element, puisqu'il est retourné
// PRECONDITION : queue non vide
char* queue_dequeue(queue_t l );

// Retourne le nombre d'éléments (ou de maillons) de la file
size_t queue_length(queue_t l);

// Affiche la file
void queue_printf(queue_t l);

// Libère toute la queue et retourne une file vide
// Libère aussi les éléments
queue_t queue_delete(queue_t l);

#endif
