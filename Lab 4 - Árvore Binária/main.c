#include "btree.h"

#include <stdio.h>

int main() {
  BTREE *btree = btree_read();

  btree_bfs(btree);
  printf("\n");

  btree_dfs_pre_order(btree);
  printf("\n");

  btree_dfs_post_order(btree);
  printf("\n");

  btree_dfs_in_order(btree);
  printf("\n");

  btree_destroy(btree);

  return 0;
}
