#include "queue.h"

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node NODE;

struct node {
    NODE *prox;
    void *element;
};

struct queue {
    NODE *in, *fim;
};

QUEUE *queue_create() {
    QUEUE *q;
    assert((q = (QUEUE *) malloc(sizeof(QUEUE))) != NULL);
    assert((q->in = (NODE *) malloc(sizeof(NODE))) != NULL);
    q->in->prox = NULL;
    q->fim = q->in;
    return q;
}

void queue_destroy(QUEUE *queue) {
    while(queue_is_empty(queue) == false)
        queue_dequeue(queue);
    free(queue->in);
    free(queue);
}

void queue_enqueue(QUEUE *queue, void *element) {
    NODE *q;
    assert((q = (NODE *) malloc(sizeof(NODE))) != NULL);
    queue->fim->prox = q;
    queue->fim = q;
    queue->fim->prox = NULL;
    queue->fim->element = element;
}

void queue_dequeue(QUEUE *queue) {
    NODE *q;
    if(queue_is_empty(queue) == false)
    {
        q = queue->in->prox;
        queue->in->prox = q->prox;
        free(q);
    }
}

void *queue_front(const QUEUE *queue) {
    if(queue_is_empty(queue) == false)
        return queue->in->prox->element;
    else
        return NULL;
}

bool queue_is_empty(const QUEUE *queue) {
    if(queue->in->prox == NULL)
        return true;
    else
        return false;
}
