/* Faça aqui sua implementação. */

#include "deque.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct deque
{
    int size;
    struct noh *fr, *tr;
};

struct noh
{
    int elem;
    struct noh *prox, *prev;
};

DEQUE *deque_create()
{
    DEQUE *deque;
    deque = (DEQUE *)malloc(sizeof(DEQUE));
    assert(deque != NULL);
    deque->fr = deque->tr = (struct noh *)malloc(sizeof(struct noh));
    assert(deque->fr != NULL);
    deque->tr->prox = NULL;
    deque->size = 0;
    return deque;
}

void deque_destroy(DEQUE *deque)
{
    deque_empty(deque);
    free(deque->fr);
    free(deque);
}

void deque_empty(DEQUE *deque)
{
    if(deque->size > 0)
    {
        struct noh *p;
        p = deque->tr;
        while(p != deque->fr)
        {
            p = p->prev;
            free(p->prox);
        }
        deque->tr = deque->fr;
        deque->tr->prox = NULL;
        deque->size = 0;
    }
}

void deque_print(const DEQUE *deque)
{
    struct noh *p;
    for(p = deque->fr; p->prox != NULL; p = p->prox)
        printf("%d ", p->prox->elem);
    printf("\n");
}

int deque_first(const DEQUE *deque)
{
    if(deque->size == 0)
        return -999999;
    else
        return deque->fr->prox->elem;
}

int deque_last(const DEQUE *deque)
{
    if(deque->size == 0)
        return -999999;
    else
        return deque->tr->elem;
}

void deque_insertFirst(DEQUE *deque, int element)
{
    if(deque->size == 0)
    {
        assert((deque->fr->prox = (struct noh *)malloc(sizeof(struct noh))) != NULL);
        deque->tr = deque->fr->prox;
        deque->tr->prev = deque->fr;
        deque->tr->prox = NULL;
        deque->tr->elem = element;
    }
    else
    {
        struct noh *p;
        p = deque->fr->prox;
        assert((deque->fr->prox = (struct noh *)malloc(sizeof(struct noh))) != NULL);
        deque->fr->prox->prox = p;
        deque->fr->prox->prev = deque->fr;
        p->prev = deque->fr->prox;
        deque->fr->prox->elem = element;
    }
    deque->size++;
}

void deque_insertLast(DEQUE *deque, int element)
{
    if(deque->fr == deque->tr)
    {
        assert((deque->fr->prox = (struct noh *)malloc(sizeof(struct noh))) != NULL);
        deque->tr = deque->fr->prox;
        deque->tr->prev = deque->fr;
        deque->tr->prox = NULL;
        deque->tr->elem = element;
    }
    else
    {
        struct noh *p;
        p = deque->tr;
        assert((p->prox = (struct noh *)malloc(sizeof(struct noh))) != NULL);
        p->prox->prev = p;
        p->prox->prox = NULL;
        deque->tr = p->prox;
        deque->tr->elem = element;
    }
    deque->size++;
}

void deque_removeFirst(DEQUE *deque)
{
    if(deque->size == 0)
        printf("ERRO!\n");
    else
    {
        struct noh *p;
        p = deque->fr->prox;
        deque->fr->prox = p->prox;
        if(p->prox == NULL)
        {
            deque->tr = deque->fr;
            free(p);
        }
        else
        {
            p->prox->prev = deque->fr;
            free(p);
        }
    deque->size--;
    }
}

void deque_removeLast(DEQUE *deque)
{
    if(deque->size == 0)
        printf("ERRO!\n");
    else
    {
        struct noh *p;
        p = deque->tr;
        deque->tr = p->prev;
        deque->tr->prox = NULL;
        deque->size--;
        free(p);
    }
}

int deque_size(const DEQUE *deque)
{
    return deque->size;
}