#include "btree.h"
#include "queue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct btree {
    char data;
    BTREE *pai, *fesq, *fdir;
};

BTREE *btree_read() {
    BTREE *btree;
    char c;

    /* raiz */

    assert(scanf(" %c", &c) == 1);
    assert(scanf(" %c", &c) == 1);
    if(c == ')')
        btree = NULL;
    else
    {
        assert((btree = (BTREE *) malloc(sizeof(BTREE))) != NULL);
        btree->data = c;
        btree->pai = NULL;
        btree->fesq = btree_read();
        if(btree->fesq != NULL)
            btree->fesq->pai = btree;
        btree->fdir = btree_read();
        if(btree->fdir != NULL)
            btree->fdir->pai = btree;
        assert(scanf(" %c", &c) == 1);
    }

    return btree;
}

void btree_destroy(BTREE *btree) {
    if(btree != NULL)
    {
        btree_destroy(btree->fesq);
        btree_destroy(btree->fdir);
        free(btree);
    }
}

void btree_dfs_pre_order(const BTREE *btree) {
    if(btree != NULL)
    {
        printf("%c", btree->data);
        btree_dfs_pre_order(btree->fesq);
        btree_dfs_pre_order(btree->fdir);
    }
}

void btree_dfs_post_order(const BTREE *btree) {
    if(btree != NULL)
    {
        btree_dfs_post_order(btree->fesq);
        btree_dfs_post_order(btree->fdir);
        printf("%c", btree->data);
    }
}

void btree_dfs_in_order(const BTREE *btree) {
    if(btree != NULL)
    {
        btree_dfs_in_order(btree->fesq);
        printf("%c", btree->data);
        btree_dfs_in_order(btree->fdir);
    }
}

void btree_bfs(const BTREE *btree) {
    QUEUE *queue;
    BTREE *p;
    
    p = (BTREE *) btree;    
    queue = queue_create();

    if(p != NULL)
    {
        queue_enqueue(queue, (void *) p);
        while(queue_is_empty(queue) == false)
        {
            p = (BTREE *) queue_front(queue);
            printf("%c", p->data);
            if(p->fesq != NULL)
                queue_enqueue(queue, (void *) p->fesq);
            if(p->fdir != NULL)
                queue_enqueue(queue, (void *) p->fdir);
            queue_dequeue(queue);
        }
    }

    queue_destroy(queue);
}
