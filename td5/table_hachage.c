#include <stdlib.h>
#include <stdio.h>
// Inclusion des listes génériques
#include "src/list.c"

///////// Les maillons des listes génériques contiennent des pointeurs vers des triplets clés, valeurs, hashcode.
///////// Le hashcode n'est utile que pour l'optimisation du redimensionnement
typedef struct {
    void* key;
    void* data;
    unsigned int hashcode;
} * cellhashltable_t;

///////// Le type des tables d'association
typedef struct {
    unsigned int total_number;
    unsigned int size;
    unsigned int (*hachage)(void *);
    link_t * data;
    void* (*delete_key)(void*);
    void* (*delete_data)(void*);
    int (*compare_key)(void* e1, void* e2);
    void (*print_key)(void*,FILE*);
    void (*print_data)(void*,FILE*);
}* hashltable_t;

hashltable_t hashltable_new(int n, unsigned int (*fhachage)(void * ),
    void* (*delete_key)(void*), void* (*delete_data)(void*),
    int (*compare_key)(void* e1, void* e2),
    void (*print_key)(void*,FILE*), void (*print_data)(void*,FILE*)) {
    hashltable_t table = (hashltable_t)malloc(sizeof(*table));
    if (!table) return NULL;

    table->total_number = 0;
    table->size = n;
    table->hachage = fhachage;
    table->data = (link_t *)calloc(n, sizeof(link_t));
    table->delete_key = delete_key;
    table->delete_data = delete_data;
    table->compare_key = compare_key;
    table->print_key = print_key;
    table->print_data = print_data;

    return table;
}

hashltable_t hashltable_delete(hashltable_t table) {
    if (!table) return NULL;

    for (unsigned int i = 0; i < table->size; i++) {
    link_t current = table->data[i];
    while (current) {
        link_t next = current->next;
        cellhashltable_t cell = (cellhashltable_t)current->data;
        table->delete_key(cell->key);
        table->delete_data(cell->data);
        free(cell);
        free(current);
        current = next;
    }
    }
    free(table->data);
    free(table);
    return NULL;
}

int hashltable_put(void* key, void* data, hashltable_t table) {
    unsigned int hashcode = table->hachage(key);
    unsigned int index = hashcode % table->size;

    link_t current = table->data[index];
    while (current) {
        cellhashltable_t cell = (cellhashltable_t)current->data;
        if (table->compare_key(cell->key, key) == 0) {
            table->delete_data(cell->data);
            cell->data = data;
            return 0;
        }
        current = current->next;
    }

    cellhashltable_t new_cell = (cellhashltable_t)malloc(sizeof(*new_cell));
    if (!new_cell) return -1;
    new_cell->key = key;
    new_cell->data = data;
    new_cell->hashcode = hashcode;

    link_t new_link = (link_t)malloc(sizeof(*new_link));
    if (!new_link) {
        free(new_cell);
        return -1;
    }
    new_link->data = (void*)(void*)new_cell;
    new_link->next = table->data[index];
    table->data[index] = new_link;

    table->total_number++;
    return 0;
}

void* hashltable_get_value(void* key, hashltable_t table) {
    unsigned int hashcode = table->hachage(key);
    unsigned int index = hashcode % table->size;

    link_t current = table->data[index];
    while (current) {
    cellhashltable_t cell = (cellhashltable_t)current->data;
    if (table->compare_key(cell->key, key) == 0) {
        return cell->data;
    }
    current = current->next;
    }
    return NULL;
}

void hashltable_remove_key(void* key, hashltable_t table) {
    unsigned int hashcode = table->hachage(key);
    unsigned int index = hashcode % table->size;

    link_t current = table->data[index];
    link_t prev = NULL;
    while (current) {
    cellhashltable_t cell = (cellhashltable_t)current->data;
    if (table->compare_key(cell->key, key) == 0) {
        if (prev) {
        prev->next = current->next;
        } else {
        table->data[index] = current->next;
        }
        table->delete_key(cell->key);
        table->delete_data(cell->data);
        free(cell);
        free(current);
        table->total_number--;
        return;
    }
    prev = current;
    current = current->next;
    }
}

void hashltable_fprintf(hashltable_t table, FILE* fp) {
    for (unsigned int i = 0; i < table->size; i++) {
    link_t current = table->data[i];
    while (current) {
        cellhashltable_t cell = (cellhashltable_t)current->data;
        table->print_key(cell->key, fp);
        fprintf(fp, ": ");
        table->print_data(cell->data, fp);
        fprintf(fp, "\n");
        current = current->next;
    }
    }
}

void hashltable_printf(hashltable_t table) {
    hashltable_fprintf(table, stdout);
}

unsigned int simple_hash(void* key) {
    return *((unsigned int*)key);
}

void* delete_key(void* key) {
    free(key);
    return NULL;
}

void* delete_data(void* data) {
    free(data);
    return NULL;
}

int compare_key(void* e1, void* e2) {
    return *((unsigned int*)e1) - *((unsigned int*)e2);
}

void print_key(void* key, FILE* fp) {
    fprintf(fp, "%u", *((unsigned int*)key));
}

void print_data(void* data, FILE* fp) {
    fprintf(fp, "%s", (char*)data);
}

int main() {
    hashltable_t table = hashltable_new(10, simple_hash, delete_key, delete_data, compare_key, print_key, print_data);

    unsigned int* key1 = (unsigned int*)malloc(sizeof(unsigned int));
    *key1 = 1;
    char* data1 = strdup("data1");
    hashltable_put(key1, data1, table);

    unsigned int* key2 = (unsigned int*)malloc(sizeof(unsigned int));
    *key2 = 2;
    char* data2 = strdup("data2");
    hashltable_put(key2, data2, table);

    hashltable_printf(table);

    char* value = (char*)hashltable_get_value(key1, table);
    if (value) {
        printf("Value for key %u: %s\n", *key1, value);
    }

    hashltable_remove_key(key1, table);
    hashltable_printf(table);

    hashltable_delete(table);
    return 0;
}