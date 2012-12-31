
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
** Join list's nodes to a string according a separator.
*/

char *list_join(t_list *this, char *sep) {
  t_node *it;
  char *str;
  int sep_len;
  int str_len;
  int i;

  it = this->head;
  sep_len = strlen(sep);
  str_len = 0;
  for (i = 0 ; i < this->length ; i++) {
    str_len += strlen(it->val) + sep_len;
    it = it->next;
  }
  if (!(str = malloc(sizeof(char) * str_len)))
    return NULL;
  it = this->head;
  str[0] = 0;
  for (i = 0 ; i < this->length ; i++) {
    str = strcat(str, it->val);
    if (i + 1 != this->length)
      str = strcat(str, sep);
    it = it->next;
  }
  return str;
}