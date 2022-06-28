/* Não modifique este arquivo. */

#include "stack_extra.h"

#include <stdio.h>

static void check_stack(STACK *stack) {
  while (!stack_isEmpty(stack))
    printf("%d ", stack_top(stack)), stack_pop(stack);
  printf("\n");
}

int main() {

  char cmd;
  int element, size_a, size_b;
  STACK *a, *b;

  while (scanf("%c", &cmd) != EOF) {

    switch (cmd) {
    case 't':
      a = stack_create();

      scanf("%d", &size_a);
      while (size_a-- > 0)
        scanf("%d", &element), stack_push(a, element);

      stack_printTopDown(a);
      check_stack(a);
      stack_destroy(a);

      break;

    case 'b':
      a = stack_create();

      scanf("%d", &size_a);
      while (size_a-- > 0)
        scanf("%d", &element), stack_push(a, element);

      stack_printBottomUp(a);
      check_stack(a);
      stack_destroy(a);

      break;

    case 'r':
      a = stack_create();

      scanf("%d", &size_a);
      while (size_a-- > 0)
        scanf("%d", &element), stack_push(a, element);

      b = stack_reverse(a);

      check_stack(b);
      check_stack(a);

      stack_destroy(b);
      stack_destroy(a);

      break;

    case 's':
      a = stack_create();
      b = stack_create();

      scanf("%d %d", &size_a, &size_b);

      while (size_a-- > 0)
        scanf("%d", &element), stack_push(a, element);

      while (size_b-- > 0)
        scanf("%d", &element), stack_push(b, element);

      stack_stack(a, b);

      check_stack(a);
      check_stack(b);

      stack_destroy(a);
      stack_destroy(b);

      break;
    }
  }

  return 0;
}
