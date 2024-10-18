#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/list.c"

// Definition de la structure
typedef struct {
    /* Nombre d'elements de l'ensemble */
    unsigned int total_number;
    /* Taille du tableau */
    unsigned int size;
    /* La fonction de hachage pour cet ensemble */
    unsigned int (*hachage)(char *);
    /* Le tableau de pointeurs vers maillons */
    link_t * data;  
    /* Les fonctions classiques */
    char* (*delete_key)(char*);
    int (*compare_key)(char* e1, char* e2);
    void (*print_key)(char*, FILE*);
}* hashset_t;


// prototypes des fonctions

unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash;
}

void print_key(char *key, FILE *fp) {
    fprintf(fp, "%s\n", key);
}

char* delete_key(char *key) {
    free(key);
    return NULL;
}

int compare_key(char *e1, char *e2) {
    return strcmp(e1, e2);
}

// Creation d'un ensemble vide de taille n
hashset_t hashset_new(int n, unsigned int (*fhachage)(char *),
        void (*print_key)(char*, FILE*), char* (*delete_key)(char*),
        int (*compare_key)(char* e1, char* e2)) {
            
    hashset_t table = (hashset_t)malloc(sizeof(*table));
    if (table == NULL) {
      fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
    }

    table->total_number = 0;
    table->size = n;
    table->hachage = fhachage;
    table->print_key = print_key;
    table->delete_key = delete_key;
    table->compare_key = compare_key;
    table->data = (link_t *)calloc(n, sizeof(link_t));

    if (table->data == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      free(table);
      exit(EXIT_FAILURE);
    }

    return table;
}

hashset_t hashset_delete(hashset_t table) {
    if (table == NULL) return NULL;

    for (unsigned int i = 0; i < table->size; i++) {
      link_t current = table->data[i];
      while (current != NULL) {
        link_t temp = current;
        current = current->next;
        table->delete_key(temp->data);
        free(temp);
      }
    }

    free(table->data);
    free(table);
    return NULL;
}

int hashset_put(char* key, hashset_t table) {
    unsigned int index = table->hachage(key) % table->size;
    link_t current = table->data[index];

    while (current != NULL) {
      if (table->compare_key(current->data, key) == 0) {
        return 1; // Key already exists
      }
      current = current->next;
    }

    link_t new_link = (link_t)malloc(sizeof(*new_link));
    if (new_link == NULL) {
      fprintf(stderr, "Memory allocation error\n");
      return 0;
    }

    new_link->data = key;
    new_link->next = table->data[index];
    table->data[index] = new_link;
    table->total_number++;
    return 1;
}

int hashset_find_key(char* key, hashset_t table) {
    unsigned int index = table->hachage(key) % table->size;
    link_t current = table->data[index];

    while (current != NULL) {
      if (table->compare_key(current->data, key) == 0) {
        return 1; // Key found
      }
      current = current->next;
    }

    return 0; // Key not found
}
int hashset_remove_key(char* key, hashset_t table) {
    unsigned int index = table->hachage(key) % table->size;
    link_t current = table->data[index];
    link_t prev = NULL;

    while (current != NULL) {
        if (table->compare_key(current->data, key) == 0) {
            if (prev == NULL) {
                table->data[index] = current->next;
            } else {
                prev->next = current->next;
            }
            table->delete_key(current->data);
            free(current);
            table->total_number--;
            return 1; // Key removed
        }
        prev = current;
        current = current->next;
    }

    return 0; // Key not found
}

void hashset_fprintf(hashset_t table, FILE* fp) {
    for (unsigned int i = 0; i < table->size; i++) {
      link_t current = table->data[i];
      while (current != NULL) {
        table->print_key(current->data, fp);
        current = current->next;
      }
    }
}

int main() {

    // Create a new hashset
    hashset_t my_hashset = hashset_new(10, hash_function, print_key, delete_key, compare_key);

    // Add some keys
    char *key1 = strdup("key1");
    char *key2 = strdup("key2");
    char *key3 = strdup("key3");

    hashset_put(key1, my_hashset);
    hashset_put(key2, my_hashset);
    hashset_put(key3, my_hashset);

    // Find keys
    printf("Find key1: %d\n", hashset_find_key("key1", my_hashset));
    printf("Find key4: %d\n", hashset_find_key("key4", my_hashset));

    // Print all keys
    printf("All keys:\n");
    hashset_fprintf(my_hashset, stdout);

    // Remove a key
    printf("Remove key2: %d\n", hashset_remove_key("key2", my_hashset));

    // Print all keys after removal
    printf("All keys after removal:\n");
    hashset_fprintf(my_hashset, stdout);

    // Delete the hashset
    my_hashset = hashset_delete(my_hashset);

    return 0;
}