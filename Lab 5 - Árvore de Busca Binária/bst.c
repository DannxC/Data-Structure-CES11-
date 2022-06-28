#include "bst.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree TREE;

struct tree {
    int data;
    TREE *fesq, *fdir;
};

struct bst {
    TREE *root;
};

BST *bst_create() {
    BST *bst;

    assert((bst = (BST *) malloc(sizeof(BST))) != NULL);
    bst->root = NULL;

    return bst;
}

void bst_destroy(BST *bst) {
    BST *p, *q;

    if(bst->root != NULL)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);
        assert((q = (BST *) malloc(sizeof(BST))) != NULL);
        p->root = bst->root->fesq;
        q->root = bst->root->fdir;
        bst_destroy(p);
        bst_destroy(q);
    }

    free(bst->root);
    free(bst);
}

void bst_insert(BST *bst, int value) {
    BST *p;
    TREE *t;

    if(bst->root == NULL)
    {
        assert((t = (TREE *) malloc(sizeof(TREE))) != NULL);
        t->fesq = t->fdir = NULL;
        t->data = value;
        bst->root = t;
    }
    else if(value < bst->root->data)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);
        p->root = bst->root->fesq;
        bst_insert(p, value);
        bst->root->fesq = p->root;
    }
    else if(value > bst->root->data)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);
        p->root = bst->root->fdir;
        bst_insert(p, value);
        bst->root->fdir = p->root;
    }
}

void bst_remove(BST *bst, int value) {
    BST *p;

    if(bst->root != NULL)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);

        if(value < bst->root->data)
        {
            p->root = bst->root->fesq;
            bst_remove(p, value);
            bst->root->fesq = p->root;
        }
        else if(value > bst->root->data)
        {
            p->root = bst->root->fdir;
            bst_remove(p, value);
            bst->root->fdir = p->root;
        }
        /* tipo 1 */
        else if(bst->root->fesq == NULL && bst->root->fdir == NULL)
        {
            free(bst->root);
            bst->root = NULL;
        }
        /* tipo 2 - tem fdir */
        else if(bst->root->fesq == NULL)
        {
            p->root = bst->root;
            bst->root = bst->root->fdir;
            free(p->root);
        }
        /* tipo 2 - tem fesq */
        else if(bst->root->fdir == NULL)
        {
            p->root = bst->root;
            bst->root = bst->root->fesq;
            free(p->root);
        }
        /* tipo 3 */
        else
        {
            p->root = bst->root->fdir;
            bst->root->data = deletar_minimo(p);
            bst->root->fdir = p->root;
        }

    free(p);
    }
}

bool bst_search(const BST *bst, int value) {
    BST *p;

    if(bst->root == NULL)
        return false;
    else if(value < bst->root->data)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);
        p->root = bst->root->fesq;
        return bst_search(p, value);
    }
    else if(value > bst->root->data)
    {
        assert((p = (BST *) malloc(sizeof(BST))) != NULL);
        p->root = bst->root->fdir;
        return bst_search(p, value);
    }
    else
        return true;
}

int bst_height(const BST *bst) {
    int hesq, hdir;
    BST *p, *q;

    if(bst->root == NULL)
        return -1;

    assert((p = (BST *) malloc(sizeof(BST))) != NULL);
    assert((q = (BST *) malloc(sizeof(BST))) != NULL);
    p->root = bst->root->fesq;
    q->root = bst->root->fdir;

    hesq = bst_height(p);
    hdir = bst_height(q);

    free(p);
    free(q);

    if(hesq > hdir)
        return hesq + 1;
    else
        return hdir + 1;
}

void bst_print(const BST *bst) {
    BST *p, *q;

    assert((p = (BST *) malloc(sizeof(BST))) != NULL);
    assert((q = (BST *) malloc(sizeof(BST))) != NULL);

    if(bst->root != NULL)
    {
        p->root = bst->root->fesq;
        q->root = bst->root->fdir;
        printf("(%d", bst->root->data);
        bst_print(p);
        bst_print(q);
        printf(")");
    }
    else
        printf("()");

    free(p);
    free(q);
}

int deletar_minimo(BST *bst)
{
    BST *p;
    int ret;

    assert((p = (BST *) malloc(sizeof(BST))) != NULL);

    if(bst->root != NULL)
    {
        if(bst->root->fesq == NULL)
        {
            ret = bst->root->data;
            p->root = bst->root;
            bst->root = bst->root->fdir;
            free(p->root);
        }
        else
        {
            p->root = bst->root->fesq;
            ret = deletar_minimo(p);
            bst->root->fesq = p->root;
        }
    }

    free(p);

    return ret;
}

/*
int deletar_maximo(BST *bst)
{
    BST *p;
    int ret;

    assert((p = (BST *) malloc(sizeof(BST))) != NULL);

    if(bst->root != NULL)
    {
        if(bst->root->fdir == NULL)
        {
            ret = bst->root->data;
            p->root = bst->root;
            bst->root = bst->root->fesq;
            free(p->root);
        }
        else
        {
            p->root = bst->root->fdir;
            ret = deletar_maximo(p);
            bst->root->fdir = p->root;
        }
    }

    free(p);

    return ret;
}
*/