#include "digraph.h"

int main() {
  DIGRAPH *digraph = digraph_read();
  topological_sort(digraph);
  digraph_destroy(digraph);
}
