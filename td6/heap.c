#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/* creates a new heap with a given capacity */
heap_t heap_new(unsigned int n) {
    heap_t heap;
    heap.data = (char **)malloc(n * sizeof(char *));
    heap.size = 0;
    heap.capacity = n;
    return heap;
}

/* swaps two elements in the heap */
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

/* restores the heap property by moving the element at index  */
void heapify_up(heap_t *heap, int index) {
    if (index && strcmp(heap->data[(index - 1) / 2], heap->data[index]) < 0) {
        swap(&heap->data[(index - 1) / 2], &heap->data[index]);
        heapify_up(heap, (index - 1) / 2);
    }
}

/* adds a new element to the heap */
int heap_add(char* valeur, heap_t *tas) {
    if (tas->size == tas->capacity) {
        return -1; // heap is full
    }
    tas->data[tas->size] = strdup(valeur);
    heapify_up(tas, tas->size);
    tas->size++;
    return 0;
}

/* restores the heap property by moving the element at index down */
void heapify_down(heap_t *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && strcmp(heap->data[left], heap->data[largest]) > 0) {
        largest = left;
    }

    if (right < heap->size && strcmp(heap->data[right], heap->data[largest]) > 0) {
        largest = right;
    }

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

/* returns the maximum element in the heap */
char* heap_get_extrema(heap_t *tas) {
    if (tas->size == 0) {
        return NULL; // heap is empty
    }
    return tas->data[0];
}

/* deletes the maximum element from the heap */
int heap_delete_extrema(heap_t *tas) {
    if (tas->size == 0) {
        return -1; // heap is empty
    }
    free(tas->data[0]);
    tas->data[0] = tas->data[--tas->size];
    heapify_down(tas, 0);
    return 0;
}

/* deletes the heap and frees all allocated memory */
heap_t heap_delete(heap_t *tas) {
    for (unsigned int i = 0; i < tas->size; i++) {
        free(tas->data[i]);
    }
    free(tas->data);
    tas->data = NULL;
    tas->size = 0;
    tas->capacity = 0;
    return *tas;
}

int main() {
    heap_t heap = heap_new(10);
    heap_add("aardvark", &heap);
    heap_add("bamboozle", &heap);
    heap_add("catawampus", &heap);
    heap_add("dingleberry", &heap);
    heap_add("flibbertigibbet", &heap);
    heap_add("gobbledygook", &heap);
    heap_add("hullabaloo", &heap);

    printf("max: %s\n", heap_get_extrema(&heap));
    heap_delete_extrema(&heap);
    printf("max after deletion: %s\n", heap_get_extrema(&heap));

    heap_delete_extrema(&heap);
    printf("max after another deletion: %s\n", heap_get_extrema(&heap));

    heap = heap_delete(&heap);
    return 0;
}