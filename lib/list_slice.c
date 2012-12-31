
#include "list.h"

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
    if (i >= from && i < to)
      list_push(result, it->val);
    it = it->next;
  }
  return result;
}