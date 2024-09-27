  typedef struct _link {
    void* data;               /* un élément de la liste*/
    struct _link *next;       /* l'adresse du maillon suivant */
  } *link_t;

  typedef struct _list{
    link_t data;
    unsigned int size;

    void* (*delete_data)(void*);
    void (*fprint_data)(void*);
    int (*equal_data)(void*,void*);
  } * list_t;