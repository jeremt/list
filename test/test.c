
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

// Helpers

#define test(fn) test_##fn() /*&&*/; puts("    • "# fn " ✓"); // || ✗


static void test_list_insertion() {
  // Setup
  t_list *list = list_new();

  t_node *a = list_push(list, "a");
  t_node *b = list_unshift(list, "b");
  t_node *c = list_unshift(list, "c");

  // Assertions
  assert(list->head == c);
  assert(list->tail == a);
  assert(list->length == 3);
  assert(a->next == NULL);
  assert(a->prev == b);
  assert(b->next == a);
  assert(b->prev == c);
  assert(c->next == b);
  assert(c->prev == NULL);
}

static void test_list_deletion() {
  // Setup
  t_list *list = list_new();
  t_node *a = list_push(list, "a");
  t_node *b = list_push(list, "b");
  t_node *c = list_push(list, "c");

  // Assertions
  assert(3 == list->length);

  assert(a == list_shift(list));
  assert(2 == list->length);
  assert(b == list->head);
  
  assert(b == list_shift(list));
  assert(1 == list->length);
  
  assert(c == list_shift(list));
  assert(0 == list->length);
  assert(NULL == list->head);
  assert(NULL == list->tail);
  
  assert(NULL == list_shift(list));
  assert(0 == list->length);
}

int main(int argc, const char **argv){
  puts("");
  printf("  \x1b[1mt_list\x1b[m     %db\n",   (int)sizeof(t_list));
  printf("  \x1b[1mt_node\x1b[m     %db\n",   (int)sizeof(t_node));
  puts("");

  test(list_insertion);
  test(list_deletion);
  puts("");

  return 0;
}
