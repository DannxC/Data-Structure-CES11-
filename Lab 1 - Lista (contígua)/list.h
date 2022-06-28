#ifndef LIST_H
#define LIST_H

typedef struct list LIST; // não altere esta linha


/** Criação e destruição do TAD **/

// Criar o TAD LIST
//
// max - máximo de elementos que a lista deve suportar
LIST *list_create(unsigned int max);   // não altere esta linha

// Destroi o TAD LIST
//
// list - ponteiro para o TAD
void list_destroy(LIST *list); // não altere esta linha


/** Informações sobre o TAD **/

// Máximo de elementos suportado pelo TAD
unsigned int list_max(LIST *list);   // não altere esta linha

// Quantidade de elementos na lista
unsigned int list_size(LIST *list);  // não altere esta linha

// Imprime o valor idx na tela
void list_print(LIST *list, unsigned int idx);  // não altere esta linha


/** Operações do TAD **/
void list_insert(LIST *list, int value, unsigned int idx);  // não altere esta linha
void list_delete(LIST *list, unsigned int idx);  // não altere esta linha
int list_value(LIST *list, unsigned int idx);  // não altere esta linha
void list_change(LIST *list, int value, unsigned int idx);  // não altere esta linha

// acrescente outras declarações, caso desejar

#endif // LIST_H