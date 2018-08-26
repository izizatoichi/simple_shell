#ifndef _LINKLISTS_H_
#define _LINKLISTS_H_

#include <stdlib.h>

/**
 * struct list_s - singly linked list
 * @key: void * type pointer to the key
 * @value: void * type poiner to the value
 * @next: struct list_s ptr to the next node
 *
 * Description: singly linked list used in the shell project
 */
typedef struct list_s
{
	void *key;
	void *value;
	struct list_s *next;
} list_t;

/* linklists1.c */
list_t *add_node(list_t **head, void *key, void *value);
list_t *reverse_list(list_t **head);
void free_list(list_t **head, int flag);
int delete_node_at_index(list_t **head, unsigned int index);

#endif /* _LINKLISTS_H_ */
