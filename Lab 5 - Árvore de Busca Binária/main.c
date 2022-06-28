#include <stdio.h>

#include "bst.h"

int main() {
  char cmd;
  int value;

  BST *bst = bst_create();

  while (scanf("%c", &cmd) != EOF) {
    switch (cmd) {
    case 'i':
      scanf("%d", &value);
      bst_insert(bst, value);
      break;

    case 'r':
      scanf("%d", &value);
      bst_remove(bst, value);
      break;

    case 's':
      scanf("%d", &value);
      printf("%s\n", bst_search(bst, value) ? "true" : "false");
      break;

    case 'h':
      printf("%d\n", bst_height(bst));
      break;

    case 'p':
      bst_print(bst);
      printf("\n");
      break;
    }
  }

  bst_destroy(bst);
}
