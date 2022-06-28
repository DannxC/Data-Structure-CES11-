/* Não modifique este arquivo. */

#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque DEQUE;

/*
 * Retorna um deque recém-alocada.
 */
DEQUE *deque_create(void);

/*
 * Destrói um deque previamente criado, liberando toda sua memória.
 */
void deque_destroy(DEQUE *deque);

/*
 * Limpa o deque, removendo todos os elementos.
 */
void deque_empty(DEQUE *deque);

/*
 * Imprime todos os elementos dp deque na mesma linha separados por espaço.
 * Ao final do deque, um '\n' é escrito.
 */
void deque_print(const DEQUE *deque);

/*
 * Retorna o primeiro elemento do deque.
 */
int deque_first(const DEQUE *deque);

/*
 * Retorna o último elemento do deque.
 */
int deque_last(const DEQUE *deque);

/*
 * Insere um novo elemento `element` no início do deque.
 */
void deque_insertFirst(DEQUE *deque, int element);

/*
 * Insere um novo elemento `element` no fim do deque.
 */
void deque_insertLast(DEQUE *deque, int element);

/*
 * Remove o primeiro elemento do deque.
 */
void deque_removeFirst(DEQUE *deque);

/*
 * Remove o último elemento do deque.
 */
void deque_removeLast(DEQUE *deque);

/*
 * Retorna o número de elementos do deque.
 */
int deque_size(const DEQUE *deque);

#endif // DEQUE_H
