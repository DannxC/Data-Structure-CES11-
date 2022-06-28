#include "digraph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;

struct edge {
    int index;
    EDGE *next;
};

struct digraph {
    int order;
    EDGE **vertex;
};

DIGRAPH *digraph_read() {
    DIGRAPH *digraph;
    int u, v, order;

    scanf("%d", &order);
    digraph = digraph_create(order);

    while(scanf(" %d", &u) != EOF)
    {
        scanf(" %d", &v);
        digraph_add_edge(digraph, u, v);
    }

    return digraph;
}

DIGRAPH *digraph_create(int order) {
    DIGRAPH *digraph;
    int i;

    assert((digraph = (DIGRAPH *) malloc(sizeof(DIGRAPH))) != NULL);
    digraph->order = order;
    assert((digraph->vertex = (EDGE **) malloc(digraph->order * sizeof(EDGE *))) != NULL);
    for(i = 0; i < digraph->order; i++)
    {
        assert((digraph->vertex[i] = (EDGE *) malloc(sizeof(EDGE))) != NULL);   //Com noh lider
        digraph->vertex[i]->next = NULL;
    }

    return digraph;
}

void digraph_destroy(DIGRAPH *digraph) {
    EDGE *p, *q;
    int i;

    for(i = 0; i < digraph->order; i++)
    {
        p = digraph->vertex[i];
        while(p != NULL)
        {
            q = p;
            p = p->next;
            free(q);
        }
    }

    free(digraph->vertex);
    free(digraph);
}

void digraph_add_edge(DIGRAPH *digraph, int u, int v) { //ordenado  (u -> v)
    EDGE *p, *e;

    if(!digraph_has_edge(digraph, u, v))
    {
        assert((e = (EDGE *) malloc(sizeof(EDGE))) != NULL);
        e->index = v;
        for(p = digraph->vertex[u]; p->next != NULL && p->next->index < v; p = p->next);
        e->next = p->next;
        p->next = e;
    }
}

bool digraph_has_edge(const DIGRAPH *digraph, int u, int v) {
  EDGE *p;

  for(p = digraph->vertex[u]->next; p != NULL && p->index != v; p = p->next);
  if(p == NULL)
    return false;
  else
    return true;
}

COLOR *color_create(int order)
{
    int i;
    COLOR* color;

    color = (COLOR *) malloc(order * sizeof(COLOR));
    for(i = 0; i < order; i++)
        color[i] = WHITE;

    return color;
}

void color_destroy(COLOR *color)
{
    free(color);
}

// Returns false if is not dag
bool topological_sort_dfs(const DIGRAPH *digraph, int u, COLOR *color, STACK *stack) {
    EDGE *p;
    bool isDag = true;

    if(color[u] == GRAY)
        isDag = false;
    else if(color[u] == WHITE)
    {
        color[u] = GRAY;
        for(p = digraph->vertex[u]->next; p != NULL && isDag; p = p->next)
            isDag = topological_sort_dfs(digraph, p->index, color, stack);
        if(isDag)
        {
            color[u] = BLACK;
            stack_push(stack, u);
        }
    }

    return isDag;
}

void topological_sort(const DIGRAPH *digraph) {
    COLOR *color;
    STACK *stack;
    int i;
    bool isDag = true;

    stack = stack_create(); //servirá para guardar os valores BLACK, na ordem desejada pelo algoritmo da DFS;
    color = color_create(digraph->order);

    /* Rodar o algoritmo para todos os WHITE's, incluindo remanescentes */
    
    for(i = 0; i < digraph->order && isDag; i++)
        if(color[i] == WHITE)
            isDag = topological_sort_dfs(digraph, i, color, stack);
    
    /* Print da stack */

    if(isDag)
        while(!stack_isEmpty(stack))
        {
            printf("%d ", stack_top(stack));
            stack_pop(stack);
        }
    printf("\n");
    stack_destroy(stack);
    color_destroy(color);
}
