
#include "list.h"

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