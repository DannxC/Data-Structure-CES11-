/* Faça aqui sua solução. */

#include "stack_extra.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void stack_printBottomUp(STACK *stack)
{
    STACK *p;
    p = stack_create();
    while(!stack_isEmpty(stack))
    {
        stack_push(p, stack_top(stack));
        stack_pop(stack);
    }
    while(!stack_isEmpty(p))
    {
        printf("%d ", stack_top(p));
        stack_push(stack, stack_top(p));
        stack_pop(p);
    }
    free(p);
    printf("\n");
}

void stack_printTopDown(STACK *stack)
{
    STACK *p;
    p = stack_create();
    while(!stack_isEmpty(stack))
    {
        printf("%d ", stack_top(stack));
        stack_push(p, stack_top(stack));
        stack_pop(stack);
    }
    while(!stack_isEmpty(p))
    {
        stack_push(stack, stack_top(p));
        stack_pop(p);
    }
    free(p);
    printf("\n");
}

STACK *stack_reverse(STACK *stack)
{
    STACK *p, *stackinvertido;
    p = stack_create();
    stackinvertido = stack_create();
    while(!stack_isEmpty(stack))
    {
        stack_push(stackinvertido, stack_top(stack));
        stack_push(p, stack_top(stack));
        stack_pop(stack);
    }
    while(!stack_isEmpty(p))
    {
        stack_push(stack, stack_top(p));
        stack_pop(p);
    }
    free(p);
    return stackinvertido;
}

void stack_stack(STACK *a, STACK *b)
{
    STACK *p;
    p = stack_create();
    while(!stack_isEmpty(b))
    {
        stack_push(p, stack_top(b));
        stack_pop(b);
    }
    while(!stack_isEmpty(p))
    {
        stack_push(a, stack_top(p));
        stack_pop(p);
    }
    free(p);
}