
#include <stdlib.h>
#include "list.h"

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