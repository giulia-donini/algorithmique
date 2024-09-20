/* Réaliser le même travail pour des tableaux de chaines de caractères qui vous seront utiles en projet. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    char** data  ;     // les données du tableau
    size_t size;    // la taille maximale
} * table_t;

// fonction de création d'un tableau de n éléments
table_t table_new(int n) {
    table_t tab;

    // allocation de la structure
    tab=calloc(1,sizeof(*tab));
    tab->size=n;

    // allocation des données
    if ((tab->data=calloc(n,sizeof(*(tab->data))))==NULL) {
        free(tab);
        return NULL;
    }
    return tab;
}

// fonction de suppression du tableau
table_t table_delete(table_t tab){
    // libérer chaque chaîne de caractères
    for (int i = 0; i < tab->size; i++) {
        free(tab->data[i]);
    }
    free(tab->data);  // libérer le tableau de pointeurs
    free(tab);        // libérer la structure
    return NULL;
}

// fonction d'affichage du tableau
table_t table_printf(table_t tab){
    for (int i=0; i<tab->size; i++)
        printf("%s ", (tab->data[i]));
    printf("\n");
    return tab;
}

// fonction d'ajout d'un element en fin de tableau
table_t table_append(char* val, table_t tab){
    char** tmp = realloc(tab->data, (tab->size + 1) * sizeof(char*));
    if (tmp == NULL) {
        return NULL;
    }
    tab->data = tmp;
    tab->data[tab->size] = strdup(val); ;
    tab->size += 1;
    return tab;
}

// fonction d'insertion d'un element en position index dans le tableau
table_t table_insert_at(char* val, int index, table_t tab){

    if (index < 0 || index > tab->size) {
        return NULL; 
    }

    // réallouer de la mémoire pour le tableau avec une taille augmentée
    char** tmp = realloc(tab->data, (tab->size + 1)* sizeof(char*));
    if (tmp == NULL) {
        return NULL; 
    }

    // déplace les éléments à partir de l'index vers la droite
    if (index < tab->size) {
        memmove(&tmp[index + 1], &tmp[index], (tab->size - index)* sizeof(char*));
    }

    tmp[index] = strdup(val);

    // mettre à jour le pointeur du tableau et la taille
    tab->data = tmp;
    tab->size += 1;

    return tab; 
}

// fonction de suppression de l'element en position index dans le tableau
table_t table_remove_at(int index, table_t tab){

    if (index < 0 || index > tab->size) {
        return NULL; 
    }

    free(tab->data[index]); 

    // déplacez les éléments après l'index vers la gauche
    if (index < tab->size - 1) {
        memmove(&tab->data[index], &tab->data[index + 1], (tab->size - index - 1)* sizeof(char*));
    }

    // réduisez la taille du tableau
    char** tmp = realloc(tab->data, (tab->size - 1)* sizeof(char*));
    if (tmp == NULL && tab->size > 1) {
        return NULL; 
    }

    // mettre à jour la structure avec le tableau redimensionné et la nouvelle taille
    tab->data = tmp;
    tab->size -= 1;

    return tab; 

}

int main() { 
    int n;
    table_t ptab;

    // creation du tableau
    printf("taille du tableau ? \n"); scanf ("%d",&n);
    ptab= table_new(n);

    // lecture clavier
    printf("écrire les éléments\n");
    for (int i = 0; i < ptab->size; i++) {
        char buffer[100];
        scanf("%s", buffer);
        ptab->data[i] = strdup(buffer);  // Dupliquer la chaîne entrée
    }
    table_printf(ptab);

    // ajouter des éléments à la fin
    printf("ajout 2 éléments à la fin du tableau\n");
    table_append("chaine1", ptab);
    table_append("chaine2", ptab);
    table_printf(ptab);

    // insérer un élément
    printf("insertion d'un élément (valeur 20.5) à l'index 2\n");
    table_insert_at("insertion", 2, ptab);
    table_printf(ptab);

    // Supprimer un élément
    printf("suppression de l'élément à l'index 1\n");
    table_remove_at(1, ptab);
    table_printf(ptab);

    // supprimer le tableau
    table_delete(ptab);

    return 0;
}

