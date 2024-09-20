#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Programmer les différentes fonctions réalisant l'interface de programmation du type vect_t 
// pour des réels double précision, puis pour des chaines de caractères.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _vect_t {
  double* data;
  unsigned int max_size;
  unsigned int actual_size;

  void (*fprint_data)(void*,FILE*);
  void* (*delete_data)(void*);
  int (*equal_data)(void*,void*);
  }  * vect_t;

vect_t vect_new(unsigned int n,void (*fprint_data)(void*,FILE*),
        void* (*delete_data)(void*),int (*equal_data)(void*,void*)){
    
    int i;
    vect_t vecr;

    // Allocation de la structure
    if ( (vecr=malloc(sizeof(*vecr)))==NULL)
        return NULL;

    // Mise a jour des tailles max et actuelle
    vecr->max_size=n;
    vecr->actual_size=0;
    vecr->delete_data=delete_data;
    vecr->equal_data=equal_data;
    vecr->fprint_data=fprint_data;
    
}