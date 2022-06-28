#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "stack.h"

#include <stdbool.h>

typedef struct digraph DIGRAPH;

typedef enum { WHITE, GRAY, BLACK } COLOR;  //WHITE: não foi visitado ; GRAY: está sendo processado ; BLACK: já foi processado

DIGRAPH *digraph_read();

DIGRAPH *digraph_create(int order);
void digraph_destroy(DIGRAPH *digraph);

void digraph_add_edge(DIGRAPH *digraph, int u, int v);
bool digraph_has_edge(const DIGRAPH *digraph, int u, int v);

COLOR *color_create(int order);
void color_destroy(COLOR *color);

bool topological_sort_dfs(const DIGRAPH *digraph, int u, COLOR *color, STACK *stack);
void topological_sort(const DIGRAPH *digraph);

#endif // DIGRAPH_H
