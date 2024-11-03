#ifndef HEAP_H
#define HEAP_H

typedef struct {
    char** data;
    unsigned int size;
    unsigned int capacity;
} heap_t;

// create a new heap with a given capacity
heap_t heap_new(unsigned int n);

// add a value to the heap
int heap_add(char* valeur, heap_t *tas);

// get the maximum (or minimum) value from the heap
char* heap_get_extrema(heap_t *tas);

// delete the maximum (or minimum) value from the heap
int heap_delete_extrema(heap_t *tas);

// delete the heap and free its resources
heap_t heap_delete(heap_t *tas);

#endif