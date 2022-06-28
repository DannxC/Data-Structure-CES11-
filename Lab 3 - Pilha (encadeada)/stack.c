/* Faça aqui sua solução conforme visto em aula. */

#include "stack.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct noh noh;

struct stack
{
    noh *s;
};

struct noh
{
    int elem;
    noh *prox;
};

STACK *stack_create()
{
    STACK *stack;
    assert((stack = (STACK *)malloc(sizeof(STACK))) != NULL);
    stack->s = NULL;
    return stack;
}

void stack_destroy(STACK *stack)
{
    while(!stack_isEmpty(stack))
        stack_pop(stack);
    free(stack);
}

bool stack_isEmpty(const STACK *stack)
{
    if(stack->s == NULL)
        return true;
    else
        return false;
}

int stack_top(const STACK *stack)
{
    if(stack_isEmpty(stack) == true)
        return -999999;
    else
        return stack->s->elem;
}

void stack_push(STACK *stack, int element)
{
    noh *temp;
    temp = stack->s;
    assert((stack->s = (noh *)malloc(sizeof(noh))) != NULL);
    stack->s->elem = element;
    stack->s->prox = temp;
}

void stack_pop(STACK *stack)
{
    if(stack_isEmpty(stack) == false)
    {
        noh *temp;
        temp = stack->s;
        stack->s = stack->s->prox;
        free(temp);
    }
}