
#include <stdlib.h>
#include "list.h"

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