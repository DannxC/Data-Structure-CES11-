/* Não modifique este arquivo. */

#include "deque.h"

#include <assert.h>
#include <stdio.h>

int main() {
  char cmd;
  int top = 0;
  DEQUE *deques[100];

  int element;
  char pos;

  while (scanf("%c", &cmd) != EOF) {
    assert(top >= 0);
    assert(top < 100);

    switch (cmd) {
    case 'c':
      deques[top++] = deque_create();
      break;

    case 'd':
      deque_destroy(deques[--top]);
      break;

    case 'e':
      deque_empty(deques[top - 1]);
      break;

    case 'p':
      deque_print(deques[top - 1]);
      break;

    case 'a':
      scanf("%c", &pos);
      printf("%d\n", (pos == 'f' ? deque_first : deque_last)(deques[top - 1]));
      break;

    case 'i':
      scanf("%c %d", &pos, &element);
      (pos == 'f' ? deque_insertFirst : deque_insertLast)(deques[top - 1],
                                                          element);
      break;

    case 'r':
      scanf("%c", &pos);
      (pos == 'f' ? deque_removeFirst : deque_removeLast)(deques[top - 1]);
      break;

    case 's':
      printf("%d\n", deque_size(deques[top - 1]));
      break;
    }
  }

  return 0;
}
