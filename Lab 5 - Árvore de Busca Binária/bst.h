/* Não modifique este arquivo. */

#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct bst BST;

BST *bst_create();

void bst_destroy(BST *bst);

void bst_insert(BST *bst, int value);

void bst_remove(BST *bst, int value);

bool bst_search(const BST *bst, int value);

int bst_height(const BST *bst);

void bst_print(const BST *bst);

int deletar_minimo(BST *bst);

/*
int deletar_maximo(BST *bst);
*/

#endif // BST_H
