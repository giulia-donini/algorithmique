#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef enum { EMPTY, FREE, OCCUPIED } hash_state_t;

// Le TAD :
typedef struct {
  char* key;
  unsigned int hashcode;
  hash_state_t busy;
} cellhashvset_t;

typedef struct {
  unsigned int total_number;
  unsigned int size;
  unsigned int (*hachage)(const char *);
  cellhashvset_t *data;
  void (*delete_key)(char*);
  int (*compare_key)(const char* e1, const char* e2);
  void (*print_key)(const char*, FILE*);
} *hashvset_t;

unsigned int hash_function(const char* key) {
  unsigned int hash = 0;
  while (*key) {
    hash = (hash << 5) + *key++;
  }
  return hash;
}

hashvset_t hashvset_new(int n, unsigned int (*fhachage)(const char *),
            void (*print_key)(const char*, FILE*),
            void (*delete_key)(char*), int (*compare_key)(const char* e1, const char* e2)) {
  hashvset_t table = malloc(sizeof(*table));
  table->total_number = 0;
  table->size = n;
  table->hachage = fhachage;
  table->print_key = print_key;
  table->delete_key = delete_key;
  table->compare_key = compare_key;
  table->data = calloc(n, sizeof(cellhashvset_t));
  return table;
}

hashvset_t hashvset_delete(hashvset_t table) {
  for (unsigned int i = 0; i < table->size; i++) {
    if (table->data[i].busy == OCCUPIED) {
      table->delete_key(table->data[i].key);
    }
  }
  free(table->data);
  free(table);
  return NULL;
}

int hashvset_put(const char* key, hashvset_t table) {
  unsigned int hashcode = table->hachage(key);
  unsigned int index;
  unsigned int i = 0;
  do {
    index = (hashcode + i) % table->size;
    if (table->data[index].busy == EMPTY) {
      table->data[index].key = strdup(key);
      table->data[index].hashcode = hashcode;
      table->data[index].busy = OCCUPIED;
      table->total_number++;
      return 1;
    } else if (table->data[index].busy == OCCUPIED && table->compare_key(table->data[index].key, key) == 0) {
      return 1;
    }
    i++;
  } while (i < table->size);
  return 0;
}
int hashvset_remove_key(const char* key, hashvset_t table) {
  unsigned int hashcode = table->hachage(key);
  unsigned int index;
  unsigned int i = 0;
  do {
    index = (hashcode + i) % table->size;
    if (table->data[index].busy == OCCUPIED && table->compare_key(table->data[index].key, key) == 0) {
      table->delete_key(table->data[index].key);
      table->data[index].busy = FREE;
      table->total_number--;
      return 1;
    }
    i++;
  } while (i < table->size && table->data[index].busy != EMPTY);
  return 0;
}

int hashvset_find_key(const char* key, hashvset_t table) {
  unsigned int hashcode = table->hachage(key);
  unsigned int index;
  unsigned int i = 0;
  do {
    index = (hashcode + i) % table->size;
    if (table->data[index].busy == OCCUPIED) {
      if (table->compare_key(table->data[index].key, key) == 0) {
        return i;
      } else {
        i++;
      }
    } else {
      return -1;
    }
  } while (i < table->size);
  return -1;
}

void hashvset_printf(hashvset_t table) {
  for (unsigned int i = 0; i < table->size; i++) {
    if (table->data[i].busy == OCCUPIED) {
      table->print_key(table->data[i].key, stdout);
      printf("\n");
    }
  }
}

void hashvset_fprintf(hashvset_t t, FILE* fp) {
  for (unsigned int i = 0; i < t->size; i++) {
    if (t->data[i].busy == OCCUPIED) {
      t->print_key(t->data[i].key, fp);
      fprintf(fp, "\n");
    }
  }
}

int hashvset_new_length(int sens, hashvset_t table) {
  unsigned int new_size = table->size + sens;
  cellhashvset_t* new_data = calloc(new_size, sizeof(cellhashvset_t));
  for (unsigned int i = 0; i < table->size; i++) {
    if (table->data[i].busy == OCCUPIED) {
      unsigned int hashcode = table->data[i].hashcode;
      unsigned int index = hashcode % new_size;
      unsigned int j = 0;
      while (new_data[index].busy == OCCUPIED) {
        index = (hashcode + ++j) % new_size;
      }
      new_data[index] = table->data[i];
    }
  }
  free(table->data);
  table->data = new_data;
  table->size = new_size;
  return new_size;
}

void print_key(const char* key, FILE* fp) {
  fprintf(fp, "%s", key);
}

void delete_key(char* key) {
  free(key);
}

int compare_key(const char* e1, const char* e2) {
  return strcmp(e1, e2);
}

int main() {
  hashvset_t table = hashvset_new(10, hash_function, print_key, delete_key, compare_key);

  hashvset_put("apple", table);
  hashvset_put("banana", table);
  hashvset_put("cherry", table);

  printf("Table after adding keys:\n");
  hashvset_printf(table);

  printf("\nFinding 'banana': %d\n", hashvset_find_key("banana", table));
  printf("Finding 'grape': %d\n", hashvset_find_key("grape", table));

  hashvset_remove_key("banana", table);
  printf("\nTable after removing 'banana':\n");
  hashvset_printf(table);

  hashvset_new_length(5, table);
  printf("\nTable after increasing size:\n");
  hashvset_printf(table);

  hashvset_delete(table);
  return 0;
}