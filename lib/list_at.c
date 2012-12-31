
#include <stdlib.h>
#include "list.h"

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