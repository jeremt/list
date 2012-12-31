
#include <stdlib.h>
#include "list.h"

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
** Delete the last node from the list
** and return the node or NULL if the list is empty.
*/

t_node *list_pop(t_list *this) {
  t_node *node;

  if (!this->length)
    return NULL;
  node = this->tail;
  if (--this->length)
    (this->tail = node->prev)->next = NULL;
  else
    this->tail = this->head = NULL;
  node->next = node->prev = NULL;
  return node;
}

/*
** Delete the first node from the list
** and return the node or NULL if the list is empty.
*/

t_node *list_shift(t_list *this) {
  t_node *node;

  if (!this->length)
    return NULL;
  node = this->head;
  if (--this->length)
    (this->head = node->next)->prev = NULL;
  else
    this->head = this->tail = NULL;
  node->next = node->prev = NULL;
  return node;
}