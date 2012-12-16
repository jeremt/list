// epitech header (make a sublime text plugin...)

#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
** Create a new t_list or return NULL on failure.
*/

t_list *list_new() {
  t_list *this;

  if (!(this = malloc(sizeof(t_list))))
    return NULL;
  this->head = NULL;
  this->tail = NULL;
  this->free = NULL;
  this->match = NULL;
  this->length = 0;
  return this;
}

/*
** Free the list.
*/

void list_destroy(t_list *this) {
  unsigned int length;
  t_node *next;
  t_node *cur;

  length = this->length;
  cur = this->head;
  while (length--) {
    next = cur->next;
    if (this->free) this->free(cur->val);
    free(cur);
    cur = next;
  }
  free(this);
}

/*
** Create a new t_node or return NULL on failure.
**
** @api private
** @param {val} a generic pointer on the data of the node
*/

static t_node *_node_new(void *val) {
  t_node *this;
  if (!(this = malloc(sizeof(t_node))))
    return NULL;
  this->prev = NULL;
  this->next = NULL;
  this->val = val;
  return this;
}

/*
** Browse the list for each node.
**
** @param {fn} function to execute for each node
*/

void list_each(t_list *this, void (*fn)(t_node *n)) {
  t_node *it;

  it = this->head;
  while (it) {
    fn(it);
    it = it->next;
  }
}


/*
** Append the list with a node
** and return the node or NULL on failure.
**
** @param {val} node's value
*/

t_node *list_push(t_list *this, void *val) {
  t_node * node;

  if (!val) return NULL;
  node = _node_new(val);
  if (this->length) {
    node->prev = this->tail;
    node->next = NULL;
    this->tail->next = node;
    this->tail = node;
  } else {
    this->head = this->tail = node;
    node->prev = node->next = NULL;
  }
  ++this->length;
  return node;
}

/*
** Delete the last node from the list
** and return the node or NULL if the list is empty.
*/

t_node *list_pop(t_list *this) {
  if (!this->length) return NULL;
  t_node *node = this->tail;
  if (--this->length) {
    (this->tail = node->prev)->next = NULL;
  } else {
    this->tail = this->head = NULL;
  }
  node->next = node->prev = NULL;
  return node;
}

/*
** Delete the first node from the list
** and return the node or NULL if the list is empty.
*/

t_node *list_shift(t_list *this) {
  if (!this->length)
    return NULL;
  t_node *node = this->head;
  if (--this->length) {
    (this->head = node->next)->prev = NULL;
  } else {
    this->head = this->tail = NULL;
  }
  node->next = node->prev = NULL;
  return node;
}

/*
** Prepend the list with a node
** and return the node or NULL on failure.
**
** @param {val} node's value
*/

t_node *list_unshift(t_list *this, void *val) {
  t_node *node;

  if (!val)
    return NULL;
  node = _node_new(val);
  if (this->length) {
    node->next = this->head;
    node->prev = NULL;
    this->head->prev = node;
    this->head = node;
  } else {
    this->head = this->tail = node;
    node->prev = node->next = NULL;
  }
  ++this->length;
  return node;
}

/*
** Return the node associated to val or NULL.
*/

t_node *list_find(t_list *this, void *val) {
  t_node *node;

  node = this->head;
  while (node) {
    if ((this->match && this->match(val, node->val)) || val == node->val)
      return node;
    node = node->next;
  }
  return NULL;
}

/*
** Return the node at the given index or NULL.
*/

t_node *list_at(t_list *this, int index) {
  t_node *it;
  t_node *node;

  if (index >= 0 && index < this->length) {
    while (index--)
      it = it->next;
    return node;
  }
  return NULL;
}

/*
** Delete the given node from the list, and possibly its value.
*/

void list_delete(t_list *this, t_node *node) {
  if (node->prev)
    node->prev->next = node->next;
  else
    this->head = node->next;
  if (node->next)
    node->next->prev = node->prev;
  else
    this->tail = node->prev;
  if (this->free)
    this->free(node);
  free(node);
  --this->length;
}

/*
** Concat a list with another.
*/

t_list *list_concat(t_list *this, t_list *list) {
  t_list *result;
  t_node *it;

  result = list_new();
  it = this->head;
  while (it) {
    list_push(result, it->val);
    it = it->next;
  }
  it = list->head;
  while (it) {
    list_push(result, it->val);
    it = it->next;
  }
  list_destroy(this);
  return result;
}

/*
** Returns the selected elements in the list, as a new list.
**
** @param {start} an integer that specifies where to start the selection
** @param {end} an integer that specifies where to end the selection (optional)
*/

t_list *list_slice(t_list *this, int from, int to) {
  t_list *result;
  t_node *it;
  int i;

  result = list_new();
  it = this->head;
  i = 0;
  if (to < 0 || to > this->length)
    to = this->length;
  for (i = 0 ; i < this->length ; i++) {
    if (from > i && i < to)
      list_push(result, it->val);
    it = it->next;
  }
  return result;
}

/*
** Perform a merge sort on the list and return the sorted list.
*/

//!\\ DOESN'T WORK !

t_list *list_sort(t_list *this, int (*fn)(t_node *a, t_node *b)) {
  t_list *result;
  t_list *left;
  t_list *right;
  int pivot;

  if (this->length <= 1)
    return this;
  result = list_new();
  pivot = this->length >> 1;
  left = list_sort(list_slice(this, 0, pivot), fn);
  right = list_sort(list_slice(this, pivot, this->length), fn);
  while (left->length && right->length)
    list_push(result, fn(left->head, right->head)
      ? list_shift(left)
      : list_shift(right)
    );
  result = list_concat(result, left);
  result = list_concat(result, right);
  return result;
}

/*
** Join list's nodes to a string according a separator.
*/

char *list_join(t_list *this, char *sep) {
  t_node *it;
  char *str;
  int sep_len;
  int str_len;
  int i;

  it = this->head;
  sep_len = strlen(sep);
  str_len = 0;
  for (i = 0 ; i < this->length ; i++) {
    str_len += strlen(it->val) + sep_len;
    it = it->next;
  }
  if (!(str = malloc(sizeof(char) * str_len)))
    return NULL;
  it = this->head;
  str[0] = 0;
  for (i = 0 ; i < this->length ; i++) {
    str = strcat(str, it->val);
    if (i + 1 != this->length)
      str = strcat(str, sep);
    it = it->next;
  }
  return str;
}


