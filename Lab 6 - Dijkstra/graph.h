#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph GRAPH;  // não altere esta linha

GRAPH *graph_read();  // não altere esta linha

GRAPH *graph_create(int order);  // não altere esta linha
void graph_destroy(GRAPH *graph);  // não altere esta linha

void graph_add_edge(GRAPH *graph, int u, int v, int w);
bool graph_has_edge(const GRAPH *graph, int u, int v);  // não altere esta linha
int graph_edge_weight(const GRAPH *graph, int u, int v);  // não altere esta linha

void graph_print(const GRAPH *graph);  // não altere esta linha

int **matrix_create(const GRAPH *graph, int u);

int minimum_path(const GRAPH *graph, int **matrix, int *vector);

int *vector_create(const GRAPH *graph);

bool vector_is_empty(const GRAPH *graph, int* vector);

void vector_destroy(int *vector);

void dijkstra(const GRAPH *graph, int u);  // não altere esta linha

// acrescente outras funções de desejar

#endif // GRAPH_H
