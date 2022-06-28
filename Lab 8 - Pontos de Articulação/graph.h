#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph GRAPH;
typedef struct vectors VECTORS;

GRAPH *graph_read();

GRAPH *graph_create(int order);
void graph_destroy(GRAPH *graph);

void graph_add_edge(GRAPH *graph, int u, int v);
bool graph_has_edge(const GRAPH *graph, int u, int v);

VECTORS *vectors_create(int order);
void vectors_destroy(VECTORS *vectors);

void findAPs_tarjan(GRAPH *graph);
void DFS(int u, VECTORS *vectors, GRAPH *graph);
void print_APs(VECTORS *vectors, int order);

#endif // GRAPH_H