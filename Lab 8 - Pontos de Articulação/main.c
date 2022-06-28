#include "graph.h"

int main()
{
  GRAPH *graph;
  graph = graph_read();
  findAPs_tarjan(graph);
  graph_destroy(graph);
}
