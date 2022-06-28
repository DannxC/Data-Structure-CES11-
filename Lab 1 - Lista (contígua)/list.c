#include "list.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct list
{
  int *L; unsigned int max, size;
};

LIST *list_create(unsigned int max)
{
  LIST *list;
  list = (LIST *) malloc(sizeof(LIST));
  list->L = (int *) malloc(max * sizeof(int));
  list->max = max;
  list->size = 0;
  return list;
}

void list_destroy(LIST *list)
{
  free(list);
}

unsigned int list_max(LIST *list) { return list->max; }

unsigned int list_size(LIST *list) { return list->size; }

void list_print(LIST *list, unsigned int idx) {
  int value = list_value(list, idx);
  printf("%d\n", value);
}



void list_insert(LIST *list, int value, unsigned int k) {
  unsigned int i;
  for(i = list_size(list); i > k; i--)
    list->L[i] = list->L[i-1];
  list->L[k] = value;
  list->size++;
}

void list_delete(LIST *list, unsigned int k) {
  unsigned int i;
  for(i = k; i < list_size(list) - 1; i++)
    list->L[i] = list->L[i+1];
  list->size--;
}

int list_value(LIST *list, unsigned int idx) {
  return list->L[idx];
}

void list_change(LIST *list, int value, unsigned int idx) {
  list->L[idx] = value;
}