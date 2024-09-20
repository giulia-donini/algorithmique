#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vect_t {
  void* * data;
  unsigned int max_size;
  unsigned int actual_size;

  void (*fprint_data)(void*,FILE*);
  void* (*delete_data)(void*);
  int (*equal_data)(void*,void*);
  }  * vect_t;

vect_t vect_new(unsigned int n,void (*print_data)(void*,FILE*),
        void* (*delete_data)(void*),int (*equal_data)(void*,void*)) ;