#ifndef _LINKLISTS_H_
#define _LINKLISTS_H_

#include <stdlib.h>

/**
 * struct list_s - singly linked list
 * @dataptr: void * type pointer to the data
 * @next: struct list_s ptr to the next node
 *
 * Description: singly linked list used in the shell project
 */
typedef struct list_s
{
	void *dataptr;
	struct list_s *next;
} list_t;

/* linklists1.c */
list_t *add_node(list_t **head, void *dataptr);
list_t *reverse_list(list_t **head);
void free_list(list_t **head, int flag);

#endif /* _LINKLISTS_H_ */
