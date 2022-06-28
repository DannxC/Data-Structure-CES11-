/* Não modifique este arquivo. */

#ifndef STACK_EXTRA_H
#define STACK_EXTRA_H

#include "stack.h"

/*
 * Imprime os valores da pilha do fundo para o cima separados por espaço.
 * No fim da impressão um '\n' é escrito.
 */
void stack_printBottomUp(STACK *stack);

/*
 * Imprime os valores da pilha do topo para o baixo separados por espaço.
 * No fim da impressão um '\n' é escrito.
 */
void stack_printTopDown(STACK *stack);

/*
 * Retorna uma nova pilha com os valores invertidos, porém mantendo a pilha de
 * entrada inalterada.
 */
STACK *stack_reverse(STACK *stack);

/*
 * Pilha a pilha `b` sobre a pilha `a`, deixando a pilha `b` vazia.
 */
void stack_stack(STACK *a, STACK *b);

#endif // STACK_EXTRA_H
