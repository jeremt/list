
#include "list.h"

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