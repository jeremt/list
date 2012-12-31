// epitech header

#include <stdlib.h>
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