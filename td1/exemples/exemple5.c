#include <stdio.h>
#include <stdlib.h>

#define catid(a,b) a##b
#define makeid(a,b) catid(a,b)

void double_fprintf(double* v,FILE* fp) { fprintf(fp,"%.2lf ",*v); }
int double_equal(double* pv1, double *pv2) { return *pv1==*pv2; }
double* double_delete(double* db) {free(db); return db;}

#define maketabletype(type) typedef struct makeid(_table,type) { \
  type* data;\
  unsigned int max_size;\
  unsigned int actual_size;\
  \
  void (*fprint_data)(type*,FILE*);\
  type* (*delete_data)(type*);\
  int (*equal_data)(type*,type*);\
}  * makeid(makeid(table_,type),_t);

  // Cette macro permet de simplifier le nom des types
#define tabletype(type) makeid(makeid(table_,type),_t)

// Une macro pour simplifier le nom des fonctions
// Elle construit le prefixe table_double pour table_double_new,....
#define tablefunction(type,func) makeid(makeid(table_,type),func)

#define maketablenew(type) \
  tabletype(type) tablefunction(type,_new)(unsigned int n,\
      void (*fprint_data)(type*,FILE*),\
      type* (*delete_data)(type*),\
      int (*equal_data)(type*,type*)) {\
    tabletype(type) table=NULL;\
    if ( (table=malloc(sizeof(*table))) ==NULL) return NULL;\
    if (n<=0) n=1;\
    if ( (table->data=calloc(n,sizeof(*(table->data)))) ==NULL) {free(table); return NULL;}\
    table->max_size=n;\
    table->actual_size=0;\
    table->fprint_data=fprint_data;\
    table->delete_data=delete_data;\
    table->equal_data=equal_data;\
    return table;\
  }

  #define maketabledelete(type) \
  tabletype(type) tablefunction(type,_delete)(tabletype(type) table) {\
    if (table==NULL) return NULL;\
      /* On libere le tableau de donnees*/\
    free(table->data); \
      /* On libere la structure*/\
    free(table); \
    return NULL;\
  }

// Definition du tableau de réel
maketabletype(double);
// Creation de la fonction d'allocation pour les tableaux de reels
maketablenew(double);

int main() {
    table_double_t t1;
    // tableau de 10 reels
  t1=table_double_new(10,double_fprintf,NULL,NULL);
    if (t1==NULL) {
    printf("Erreur allocation\n");
    exit(EXIT_FAILURE);
  }
    // On remplit avec des valeurs aléatoires
  for (int i=0; i<t1->max_size; i++)
    t1->data[i]=random() % 100;
    // On affiche
  for (int i=0; i<t1->max_size; i++)
    printf("%lf ",t1->data[i]);
    // Mais il faut liberer ....
}