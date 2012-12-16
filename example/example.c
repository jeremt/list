
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/*
** Helpers
*/

static void skill_print(t_node *n) {
  printf("    • %s\n", (char *)n->val);
}

static void num_print(t_node *n) {
  printf("    • %d\n", *((int *)n->val));
}

static int num_cmp(t_node *a, t_node *b) {
  return *((int *)(a->val)) < *((int *)(b->val));
}

static void *num(int n) {
  int *ptr;

  ptr = malloc(sizeof(int *));
  *ptr = n;
  return (void *)ptr;
}

/*
** Examples
*/

static void sort() {
  t_list *list;

  puts("\n\x1b[1m  sort example\x1b[m\n");

  list = list_new();
  list->free = free;
  list_push(list, num(42));
  list_push(list, num(21));
  list_push(list, num(-42));
  list_push(list, num(666));
  list_push(list, num(1337));
  list_each(list, num_print);

  list_destroy(list);
}

void skills() {
  t_list *skills;
  t_node *ruby;

  puts("\n\x1b[1m  skills example\x1b[m\n");
  skills = list_new();
  list_push(skills,        "c       ★ ★ ★ ☆ ☆ ");
  list_push(skills,        "c++     ★ ☆ ☆ ☆ ☆ ");
  list_push(skills,        "js      ★ ★ ★ ★ ☆ ");
  ruby = list_push(skills, "ruby    ☆ ☆ ☆ ☆ ☆ ");
  list_push(skills,        "coffee  ★ ★ ★ ★ ☆ ");
  list_push(skills,        "python  ★ ★ ☆ ☆ ☆ ");
  list_delete(skills, ruby);
  list_each(skills, skill_print);
  list_destroy(skills);
}

void groceries() {
  t_list *groceries;
  t_list *clothes;
  t_list *some;
  char *s;

  puts("\n\x1b[1m  groceries example\x1b[m\n");

  groceries = list_new();
  list_push(groceries, "pizzas");
  list_push(groceries, "beer");
  list_push(groceries, "m&m's");
  list_push(groceries, "redbull");

  clothes = list_new();
  list_push(clothes, "t-shirt");
  list_push(clothes, "shoes");
  list_push(clothes, "jean");

  groceries = list_concat(groceries, clothes);

  s = list_join(groceries, ", ");
  printf("    %s\n", s);
  free(s);

  some = list_slice(groceries, 2, 4);
  s = list_join(some, " - ");
  printf("    %s\n", s);
  free(s);

  list_destroy(some);
  list_destroy(clothes);
  list_destroy(groceries);
}

/*
** Entry point
*/

int main(void) {
  skills();
  sort();
  groceries();
  puts("");
  return 0;
}