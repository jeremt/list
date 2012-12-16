
/*
** Dependencies
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/*
** Helper to trigger test function
*/

#define test(fn) test_##fn(); \
          puts("    • "# fn " ✓");

/*
** Test insertion
*/

static void test_list_insertion() {
  // Setup
  t_list *list = list_new();

  t_node *a = list_push(list, "a");
  t_node *b = list_unshift(list, "b");
  t_node *c = list_unshift(list, "c");

  // Assertions
  assert(list->head == c);
  assert(list->tail == a);
  assert(list->head->next == b);
  assert(b->prev == c);
  assert(list->length == 3);
  list_destroy(list);
}

/*
** Test deletion
*/

static void test_list_deletion() {
  // Setup
  t_list *list = list_new();
  t_node *a = list_push(list, "a");
  t_node *b = list_push(list, "b");
  t_node *c = list_push(list, "c");

  // Assertions
  list_delete(list, a);
  assert(list->length == 2);
  assert(list->head == b);
  list_shift(list);
  assert(list->head == c);
  assert(list->length == 1);
  list_destroy(list);

}

/*
** Test free
*/

static int nb_free = 0;

static void my_free(void *data) {
  if (data != NULL) nb_free++;
}

static void test_list_free() {
  // Setup
  t_list *list = list_new();
  list->free = my_free;
  for (int i = 0 ; i < 42 ; i++)
    list_unshift(list, "a");
  list_destroy(list);

  // Assertions
  assert(nb_free == 42);
}

/*
** Test concat
*/

static void test_list_concat() {
  // Setup
  t_list *list = list_new();
  t_list *one = list_new();
  t_list *two = list_new();

  list_push(one, "a");
  list_push(one, "b");
  list_push(one, "c");

  list_push(two, "d");
  list_push(two, "e");
  list_push(two, "f");

  list = list_concat(one, two);

  // Assertions
  assert(one->length == 3);
  assert(two->length == 3);
  assert(list->length == 6);
  list_destroy(list);
}

/*
** Test find
*/

static void test_list_find() {
  // Setup

  t_list *list = list_new();

  list_push(list, "a");

  t_node *b = list_push(list, "b");

  list_push(list, "c");
  list_push(list, "d");
  list_push(list, "e");

  t_node *f = list_push(list, "f");

  t_node *find_b = list_find(list, "b");
  t_node *find_f = list_find(list, "f");
  t_node *null = list_find(list, "k");

  // Assertion
  assert(find_b == b);
  assert(find_f == f);
  assert(null == NULL);

}

/*
** Test join
*/

static void test_list_join() {
  // Setup
  t_list *list = list_new();
  list_push(list, "a");
  list_push(list, "b");
  list_push(list, "c");
  list_push(list, "d");

  // Assertions
  assert(strcmp("a, b, c, d", list_join(list, ", ")) == 0);
}

/*
** Test slice
*/

static void test_list_slice() {
  // Setup
  t_list *list = list_new();
  list_push(list, "a");
  list_push(list, "b");
  list_push(list, "c");
  list_push(list, "d");
  list_push(list, "e");
  list_push(list, "f");
  list_push(list, "g");

  // Assertions
  assert(strcmp("d, e, f", list_join(list_slice(list, 3, 6), ", ")) == 0);
}

/*
** Entry point
*/

int main(int argc, const char **argv){
  puts("");
  printf("  \x1b[1mt_list\x1b[m     %db\n",   (int)sizeof(t_list));
  printf("  \x1b[1mt_node\x1b[m     %db\n",   (int)sizeof(t_node));
  puts("");

  test(list_insertion);
  test(list_deletion);
  test(list_free);
  test(list_concat);
  test(list_find);
  test(list_join);
  test(list_slice);
  puts("");

  return 0;
}
