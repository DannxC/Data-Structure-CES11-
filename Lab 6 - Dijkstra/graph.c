#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;
struct edge {
  int index, weight;
  EDGE *next;
};

struct graph {
  int order;
  EDGE **vertex;
};

GRAPH *graph_read() {
  GRAPH *graph;
  int u, v, w, order;

  scanf("%d", &order);
  graph = graph_create(order);

  while(scanf(" %d", &u) != EOF)
  {
    scanf("%d%d", &v, &w);
    graph_add_edge(graph, u, v, w);
  }

  return graph;
}

GRAPH *graph_create(int order) {
  GRAPH *graph;
  int i;

  assert((graph = (GRAPH *) malloc(sizeof(GRAPH))) != NULL);
  graph->order = order;
  assert((graph->vertex = (EDGE **) malloc(graph->order * sizeof(EDGE *))) != NULL);
  for(i = 0; i < graph->order; i++)
  {
    assert((graph->vertex[i] = (EDGE *) malloc(sizeof(EDGE))) != NULL);  //Com noh lider! Facilita para a ordenação dos "edges" mais tarde.
    graph->vertex[i]->next = NULL;
  }

  return graph;
}

void graph_destroy(GRAPH *graph) {
  EDGE *p, *q;
  int i;

  for(i = 0; i < graph->order; i++)
  {
    p = graph->vertex[i];
    while(p != NULL)
    {
      q = p;
      p = p->next;
      free(q);
    }
  }

  free(graph->vertex);
  free(graph);
}

void graph_add_edge(GRAPH *graph, int u, int v, int w) {  //ordenado
  EDGE *p, *e;

  if(graph_has_edge(graph, u, v) == false)
  {
    /* u -> v */

    assert((e = (EDGE *) malloc(sizeof(EDGE))) != NULL);
    e->index = v;
    e->weight = w;
    for(p = graph->vertex[u]; p->next != NULL && p->next->index < v; p = p->next);
    e->next = p->next;
    p->next = e;

    /* v -> u */

    assert((e = (EDGE *) malloc(sizeof(EDGE))) != NULL);
    e->index = u;
    e->weight = w;
    for(p = graph->vertex[v]; p->next != NULL && p->next->index < v; p = p->next);
    e->next = p->next;
    p->next = e;
  }
}

bool graph_has_edge(const GRAPH *graph, int u, int v) {
  EDGE *p;

  for(p = graph->vertex[u]->next; p != NULL && p->index != v; p = p->next);
  if(p == NULL)
    return false;
  else
    return true;
}

int graph_edge_weight(const GRAPH *graph, int u, int v) {
  EDGE *p;

  for(p = graph->vertex[u]->next; p != NULL && p->index != v; p = p->next);
  if(p == NULL)
    return -999999;
  else
    return p->weight;
}

void graph_print(const GRAPH *graph) {
  for (int u = 0; u < graph->order; ++u) {
    for (int v = 0; v < graph->order; ++v)
      if (graph_has_edge(graph, u, v) == true)
        printf(" %3d", graph_edge_weight(graph, u, v));
      else
        printf("   ∞");
    printf("\n");
  }
}

int **matrix_create(const GRAPH *graph, int u)
{
  int **matrix, i;

  /* matrix: linha 0 indica o "previous" e linha 1 indica a "distancia minima atual" */
  /* obs: cada indice de coluna indica um vertex */

  assert((matrix = (int **) malloc(2 * sizeof(int *))) != NULL);
  assert((matrix[0] = (int *) malloc(graph->order * sizeof(int))) != NULL);
  assert((matrix[1] = (int *) malloc(graph->order * sizeof(int))) != NULL);

  for(i = 0; i < graph->order; i++)
  {
    matrix[0][i] = -1; //não há previous
    matrix[1][i] = 999999; //distancia "infinita"
  }
  matrix[0][u] = -2; //significa que ele é o inicio dos caminhos (diferente dos que não o são, porém também não possuem um "previous")
  matrix[1][u] = 0;

  return matrix;
}

int minimum_path(const GRAPH *graph, int **matrix, int *vector)
{
  int i, k, d = 999999; //d inicializa como infinito
  if(!vector_is_empty(graph, vector))
  {
    for(i = 0, k = 0; i < graph->order; i++)
      if(vector[i] == 0)
        if(matrix[1][i] <= d)
        {
          d = matrix[1][i];
          k = i;
        }
    return k;
  }
  else
    return -999999; //error
}

void matrix_destroy(int **matrix)
{
  free(matrix[0]);
  free(matrix[1]);
  free(matrix);
}

int *vector_create(const GRAPH *graph)
{
  int *vector, i;
  
  /* vector: cada índice represente um vertex. se o valor for 1, já foi utilizado no algoritmo de dijkstra, se for 0, não foi utilizado */

  assert((vector = (int *) malloc(graph->order * sizeof(int))) != NULL);
  for(i = 0; i < graph->order; i++)
    vector[i] = 0;

  return vector;
}

bool vector_is_empty(const GRAPH *graph, int* vector)
{
  int i;
  bool b;
  b = true;
  for(i = 0; i < graph->order; i++)
    if(vector[i] == 0)
      b = false;
  return b;
}

void vector_destroy(int *vector)
{
  free(vector);
}

void dijkstra(const GRAPH *graph, int u) {
  int i, k, **matrix, *vector;
  EDGE *p;
  STACK *stack;

  matrix = matrix_create(graph, u);
  vector = vector_create(graph);

  /* Aplicação do algorítmo de Dijkstra tendo como início do caminho o vertex "u" */

  while(!vector_is_empty(graph, vector))
  {
    k = minimum_path(graph, matrix, vector);  //neste loop, o vertex "k" será verificado
    p = graph->vertex[k]->next;
    while(p != NULL)
    {
      if(p->weight + matrix[1][k] < matrix[1][p->index] && matrix[0][k] != -1)
      {
        matrix[0][p->index] = k;
        matrix[1][p->index] = p->weight + matrix[1][k];
      }
      p = p->next;
    }

    vector[k] = 1; //atualiza o vector: k ja foi verificado
  }
  
  /* print de todos os menores caminhos que começam no vertex "u" */

  for(i = 0; i < graph->order; i++)
    if(matrix[0][i] >= 0)
    {
      stack = stack_create();
      for(k = i; k != -2; k = matrix[0][k])
        stack_push(stack, k);
      while(stack_isEmpty(stack) == false)
      {
        printf("%d ", stack_top(stack));
        stack_pop(stack);
      }
      printf(": %d\n", matrix[1][i]);
      stack_destroy(stack);
    }

  matrix_destroy(matrix);
  vector_destroy(vector);
}
