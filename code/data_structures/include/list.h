#ifndef LIST_H
#define LIST_H

struct list_node;

/*
 *  Criar uma lista nova
 */
struct list_node *list_create();

/*
 *  Eliminar uma lista
 */
void list_destroy(struct list_node *p);

/*
 *  Remover elemento indicado
 */
void list_remove(struct list_node *node);

/*
 *  Remover elemento atrás
 */
void list_remove_rear(struct list_node *p);

/*
 *  Remover elemento à frente
 */
void list_remove_front(struct list_node *p);

/*
 *  Inserir elemento atrás de
 */
int list_insert_rear(struct list_node *p, void *data);

/*
 *  Inserir elemento em posição ordenada
 */
int list_insert_front(struct list_node *p, void *data);

/*
 *  Eliminar uma lista
 */
int list_insert_sort(struct list_node *node, void *data,
		int (*cmp)(const void*, const void*));

/*
 *  Realizar ação sobre todos os elementos da lista
 */
void list_foreach(struct list_node *node,
		void (*do_it)(void *, void *), void *context);

/*
 *   Procurar por elemento com certas características
 */
struct list_node *list_search(struct list_node *list,
		bool (*predicate)(const void *, const void *), const void *context);
/*
 *  Procurar por elemento no sentido seguinte
 */
struct list_node *list_search_forward(struct list_node *list,
		bool (*predicate)(const void *, const void *), const void *context);
/*
 *  Procurar por elemento no sentido anterior
 */
struct list_node *list_search_backward(struct list_node *list,
		bool (*predicate)(const void *, const void *), const void *context);

/*
 *  Obter o elemento seguinte
 */
struct list_node *list_get_front(struct list_node *node);
/*
 *  Obter o elemento anterior
 */
struct list_node *list_get_rear(struct list_node *node);

/*
 *  Verificar se a lista está vazia
 */
int list_empty(struct list_node *node);

/*
 *  Obter o campo de dados
 */
void *list_get_data(struct list_node *node);

/*
 *  Obter número de elementos da lista
 */
size_t list_size(struct list_node *list);

#endif
