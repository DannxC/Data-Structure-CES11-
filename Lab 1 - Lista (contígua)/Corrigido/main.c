#include "list.h"

#include <assert.h>
#include <stdio.h>

int main()
{
  unsigned int max;  // máximo de elementos no TAD

  // Auxiliares para a interface com o usuário
  char cmd = 0;       // comando do usuário
  int valor;          // parâmetros do comando
  unsigned int idx;   // parâmetros do comando

  assert(scanf("%u", &max) == 1);  // de acordo com 'https://en.cppreference.com/w/c/io/fscanf'
  assert(max > 0);

  // Criar o TAD com o número máximo solicitado
  LIST *list = list_create(max);
  assert(list != NULL);


  // Interface com o usuário
  while (cmd != '0' && scanf(" %c", &cmd) != EOF)
  {

    switch (cmd)
    {
    case 'q':
      printf("%d\n", list_size(list));
      break;

    case '0':
      break;

    case 'a':   // a <valor> <idx>
      assert( scanf(" %d %u", &valor, &idx) == 2 );
      if(idx >= list_size(list))
        printf("ERRO!\n");
      else
        list_change(list, valor, idx);
      break;

    case 'i':   // i <valor> <idx>
      assert( scanf(" %d %u", &valor, &idx) == 2 );
      if(idx > list_size(list) || list_size(list) == list_max(list))
        printf("ERRO!\n");
      else
        list_insert(list, valor, idx);
      break;

    case 'd':   // d <idx>
      assert( scanf(" %u", &idx) == 1 );
      if(idx >= list_size(list))
        printf("ERRO!\n");
      else
        list_delete(list, idx);
      break;

    case 'p':   // p <idx>
      assert( scanf(" %u", &idx) == 1 );
      if(idx >= list_size(list))
        printf("ERRO!\n");
      else
        list_print(list, idx);
      break;

    default:
      printf("\nOperacao Invalida!\n\n"); // pode ser incluido uma mensagem de operação inválida
      break;
    }
  }
  list_destroy(list);
  return 0;
}
