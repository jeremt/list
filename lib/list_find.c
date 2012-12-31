
#include <stdlib.h>
#include "list.h"

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