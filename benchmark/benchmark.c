
#include <stdio.h>
#include <time.h>
#include "list.h"

static void bm(char *label, void (*fn)()) {
  printf(" \x1b[1m%18s\x1b[m", label);
  fflush(stdout);
  fn();
}

static int nnodes = 10000000;
static clock_t startTime;

static void start() {
  startTime = clock();
}

static void stop() {
  float duration = (float) (clock() - startTime) / CLOCKS_PER_SEC;
  printf(" %.4fs\n", duration);
}

static void bm_push() {
  t_list *list;
  int n;

  start();
  n = nnodes;
  list = list_new();
  while (n--)
    list_push(list, "foo");
  stop();
  list_destroy(list);
}

static void bm_unshift() {
  t_list *list;
  int n;

  start();
  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  stop();
  list_destroy(list);
}

static void bm_find() {
  t_list *list;
  int n;

  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  list_push(list, "bar");
  start();
  list_find(list, "bar");
  stop();
  list_destroy(list);
}

static void bm_pop() {
  t_list *list;
  int n;

  list = list_new();
  n = nnodes;
  while (n--) {
    list_unshift(list, "foo");
  }
  t_node *node;
  start();
  while ((node = list_pop(list)));
  stop();
  list_destroy(list);
}

static void bm_shift() {
  t_list *list;
  t_node *node;
  int n;

  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  start();
  while ((node = list_shift(list)));
  stop();
  list_destroy(list);
}

static void bm_at() {
  t_list *list;
  int n;

  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  start();
  list_at(list, 100000);
  stop();
  list_destroy(list);
}

static void bm_at2() {
  t_list *list;
  int n;

  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  start();
  list_at(list, 1000000);
  stop();
}

static void bm_at3() {
  t_list *list;
  int n;

  list = list_new();
  n = nnodes;
  while (n--)
    list_unshift(list, "foo");
  start();
  list_at(list, -100000);
  stop();
}

static void bm_concat() {
  t_list *list;
  t_list *one;
  t_list *two;
  int n;

  n = nnodes >> 1;
  one = list_new();
  while (n--)
    list_push(one, "foo");
  n = nnodes >> 1;
  two = list_new();
  while (n--)
    list_push(two, "bar");
  start();
  list = list_concat(one, two);
  stop();
  (void)list;
}

static void bm_slice() {
  t_list *list;
  int n;

  n = nnodes;
  list = list_new();
  while (n--)
    list_push(list, "foo");
  start();
  (void)list_slice(list, 0, nnodes >> 1);
  (void)list_slice(list, nnodes >> 1, nnodes);
  stop();
}

static void bm_destroy() {
  t_list *list;
  int n;

  n = nnodes;
  list = list_new();
  while (n--)
    list_push(list, "foo");
  start();
  list_destroy(list);
  stop();
}

int main(void) {
  printf("\n \x1b[1m%d nodes\x1b[m\n\n", nnodes);
  bm("unshift", bm_unshift);
  bm("push", bm_push);
  bm("shift", bm_shift);
  bm("pop", bm_pop);
  bm("find (last node)", bm_find);
  bm("at(100000)", bm_at);
  bm("at(1000000)", bm_at2);
  bm("at(-100000)", bm_at3);
  bm("concat", bm_concat);
  bm("slice", bm_slice);
  bm("destroy", bm_destroy);
  puts("");
  return 0;
}