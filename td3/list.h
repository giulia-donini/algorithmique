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
list_t list_new();

// Retourne VRAI si l est une liste vide
int list_is_empty(list_t l);
// Retourne VRAI si l est un maillon vide
int link_is_empty(link_t l);

// Retourne l'élément en tête de liste : PRECONDITION : liste non vide
char* list_first(list_t l);

// Ajoute l'élément e en tête des maillons et retourne cette tete
// Retourne la tete NON MODIFIEE en cas d'erreur
link_t link_add_first(char* c, link_t l);
// Ajoute l'élément e en tête de liste et retourne cette liste
list_t list_add_first(char* c, list_t l);

// Supprime le maillon en tête des maillons et retourne les maillons
// PRECONDITION : maillons non vide
link_t link_del_first(link_t l);
// Supprime le maillon en tête de liste et retourne la nouvelle liste
// PRECONDITION : liste non vide
list_t list_del_first(list_t l );

// Retourne le nombre d'éléments (ou de maillons) de la liste
size_t list_length(list_t l);

// Affiche la liste a l'ecran, dasn un fichier.
void list_fprintf(list_t l, FILE* fp);
void list_printf(list_t l);

// Libère toute la liste et retourne une liste vide
// Libere les elements avec delete_data si la fonction existe
list_t list_delete(list_t l);

// Ajoute en queue de liste, eventuellement
list_t list_add_last(char* c, list_t l);
link_t link_add_last(char* c, link_t l);
//Suppression en queue, eventuellement
list_t list_del_last(list_t l );
link_t link_del_last(link_t l);

// Recherche un element selon le critere compare. Retourne le maillon trouve ou NULL
link_t list_lookup(char* elem, list_t l, int(*compare)(char* c1, char* c2));
// Recherche le premier maillon contenant e,
// au sens du equal_data ou de l'egalite de pointeurs si equal_data est NULL
// ou NULL si e n'est pas dans la liste       
link_t list_find(char* c, list_t l);

// Suppression de l'element param, au sens de equal_data
list_t list_remove(char* param, list_t l);

// Les visiteurs
void list_simple_visit(list_t l, void (*)(void*,void*), void* param);
void list_visit(list_t l, int (*exec_on_value)(void*,void*), int (*exec_on_link)(list_t,void*),void* param);
