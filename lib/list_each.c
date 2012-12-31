
#include "list.h"

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