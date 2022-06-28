#ifndef BTREE_H
#define BTREE_H

typedef struct btree BTREE;

BTREE *btree_read();

void btree_destroy(BTREE *btree);

void btree_dfs_pre_order(const BTREE *btree);
void btree_dfs_post_order(const BTREE *btree);
void btree_dfs_in_order(const BTREE *btree);

void btree_bfs(const BTREE *btree);

#endif //  BTREE_H
