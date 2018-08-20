#include "linklists.h"

/**
 * add_node - adds a new node at the beginning of a linked list
 * @head: ptr to the beginning of a linked list
 * @dataptr: ptr to new element for new node
 * Return: ptr to the new linked list
 */
list_t *add_node(list_t **head, void *dataptr)
{
	list_t *new = NULL;

	new = malloc(sizeof(list_t));
	if (new)
	{
		new->dataptr = NULL;
		new->next = *head;
		if (dataptr)
			new->dataptr = dataptr;
		*head = new;
	}
	return (new);
}

/**
 * reverse_list - reverses a linked list
 * @head: list_t pointer to the linked list
 * Return: list_t pointer to the reversed list
 */
list_t *reverse_list(list_t **head)
{
	list_t *walker = NULL, *newlist = NULL;

	while (*head)
	{
		walker = *head;
		*head = (*head)->next;
		walker->next = newlist;
		newlist = walker;
	}
	*head = newlist;
	return (*head);
}

/**
 * free_list - frees a linked list and sets the head to NULL
 * @head: list_t type
 * Return: nada
 */
void free_list(list_t **head)
{
	list_t *walker = NULL;

	while (head && *head)
	{
		walker = *head;
		*head = (*head)->next;
		free(walker);
	}
}
