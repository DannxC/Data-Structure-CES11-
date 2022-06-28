#include "graph.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;
struct edge
{
  int index;
  EDGE *next;
};

struct graph
{
  int order;
  EDGE **vertex;
};

struct vectors
{
    int *disc, *low, *parent;
    bool *AP;
};

GRAPH *graph_read()
{
  GRAPH *graph;
  int u, v, order;

  scanf("%d", &order);
  graph = graph_create(order);

  while(scanf(" %d", &u) != EOF)
  {
    scanf("%d", &v);
    graph_add_edge(graph, u, v);
  }

  return graph;
}

GRAPH *graph_create(int order)
{
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

void graph_destroy(GRAPH *graph)
{
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

void graph_add_edge(GRAPH *graph, int u, int v)     //ordenado
{
  EDGE *p, *e;

  if(graph_has_edge(graph, u, v) == false)
  {
    /* u -> v */

    assert((e = (EDGE *) malloc(sizeof(EDGE))) != NULL);
    e->index = v;
    for(p = graph->vertex[u]; p->next != NULL && p->next->index < v; p = p->next);
    e->next = p->next;
    p->next = e;

    /* v -> u */

    assert((e = (EDGE *) malloc(sizeof(EDGE))) != NULL);
    e->index = u;
    for(p = graph->vertex[v]; p->next != NULL && p->next->index < v; p = p->next);
    e->next = p->next;
    p->next = e;
  }
}

bool graph_has_edge(const GRAPH *graph, int u, int v)
{
    EDGE *p;

    for(p = graph->vertex[u]->next; p != NULL && p->index != v; p = p->next);
    if(p == NULL)
        return false;
    else
        return true;
}

VECTORS *vectors_create(int order)
{
	VECTORS *vectors;
	assert((vectors = (VECTORS *) malloc(sizeof(VECTORS))) != NULL);
    assert((vectors->disc = (int *) malloc(order * sizeof(int))) != NULL);
    assert((vectors->low = (int *) malloc(order * sizeof(int))) != NULL);
    assert((vectors->parent = (int *) malloc(order * sizeof(int))) != NULL);
    assert((vectors->AP = (bool *) malloc(order * sizeof(bool))) != NULL);

    for(int i = 0; i < order; i++)
    {
        vectors->disc[i] = -1;
        vectors->low[i] = -1;
        vectors->parent[i] = -1;
        vectors->AP[i] = false;
    }

	return vectors;
}

void vectors_destroy(VECTORS *vectors)
{
	free(vectors->disc);
	free(vectors->low);
	free(vectors->parent);
	free(vectors->AP);
	free(vectors);
}

void DFS(int u, VECTORS *vectors, GRAPH *graph)
{
	static int time = 0;
	int v, children = 0;
	EDGE *e;

	vectors->disc[u] = vectors->low[u] = time;
	time += 1;
	
	for(e = graph->vertex[u]->next; e != NULL; e = e->next)			//u->v, com v um filho qualquer de u (ordenadamente)
	{
		v = e->index;
		if(vectors->disc[v] == -1)		//v não foi visitado
		{
			children += 1;
			vectors->parent[v] = u;
			DFS(v, vectors, graph);
			vectors->low[u] = (vectors->low[u] <= vectors->low[v] ? vectors->low[u] : vectors->low[v]);

			if(vectors->parent[u] == -1 && children > 1)		//C1: u não é raiz
				vectors->AP[u] = true;
			
			if(vectors->parent[u] != -1 && vectors->low[v] >= vectors->disc[u])			//C2: Pelo menos um componente será separado
				vectors->AP[u] = true;
		}
		else if(v != vectors->parent[u])		//Ignora 
			vectors->low[u] = (vectors->low[u] <= vectors->low[v] ? vectors->low[u] : vectors->low[v]);
	}
}

void print_APs(VECTORS *vectors, int order)
{
	for(int i = 0; i < order; i++)
		if(vectors->AP[i] == true)
			printf("%d\n", i);
}

void findAPs_tarjan(GRAPH *graph)
{
    VECTORS *vectors;

    //Startar os vetores
    vectors = vectors_create(graph->order);

	//algoritmo em DFS
    DFS(0, vectors, graph);

    //print dos APs
	print_APs(vectors, graph->order);

    //destruir o vectors
	vectors_destroy(vectors);
}