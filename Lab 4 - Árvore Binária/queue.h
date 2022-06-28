#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue QUEUE;

QUEUE *queue_create();

void queue_destroy(QUEUE *queue);

void queue_enqueue(QUEUE *queue, void *element);

void queue_dequeue(QUEUE *queue);

void *queue_front(const QUEUE *queue);

bool queue_is_empty(const QUEUE *queue);

#endif // QUEUE_H
