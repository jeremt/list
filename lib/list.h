// epitech header (make a sublime text plugin...)

#ifndef LIST_H_
# define LIST_H_

/*
** Library version
*/

# define VERSION "0.0.1"

/*
** t_node struct.
*/

typedef struct s_node {
  struct s_node *prev;
  struct s_node *next;
  void *val;
} t_node;

/*
** t_list struct.
*/

typedef struct {
  t_node *head;
  t_node *tail;
  unsigned int length;
  void (*free)(void *val);
  int (*match)(void *a, void *b);
} t_list;

/*
** List prototypes.
*/

t_list *list_new();

t_node *list_push(t_list *this, void *val);

t_node *list_unshift(t_list *this, void *val);

t_node *list_find(t_list *this, void *val);

t_node *list_at(t_list *this, int index);

t_node *list_pop(t_list *this);

t_node *list_shift(t_list *this);

void list_each(t_list *this, void (*fn)(t_node *n));

void list_delete(t_list *this, t_node *node);

void list_destroy(t_list *this);

t_list *list_concat(t_list *this, t_list *list);

t_list *list_slice(t_list *this, int from, int to);

char *list_join(t_list *this, char *sep);

// TODO

int list_index_of(t_list *this, t_node *n);
t_list *list_sort(t_list *this, int (*f)(t_node *a, t_node *b));
t_list *list_map(t_list *this, int (*f)(t_node *a, t_node *b));

#endif /* !LIST_H_ */
