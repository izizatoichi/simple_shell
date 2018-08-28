#include "linklists.h"

/**
 * add_node - adds a new node at the beginning of a linked list
 * @head: ptr to the beginning of a linked list
 * @key: string that contains key
 * @value: string that contains value for key
 * Return: ptr to the new linked list
 */
list_t *add_node(list_t **head, void *key, void *value)
{
	list_t *new = NULL;

	new = malloc(sizeof(list_t));
	if (new)
	{
		new->key = NULL;
		new->value = NULL;
		new->next = *head;
		if (key)
			new->key = key;
		if (value)
			new->value = value;
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
 * @flag: flag 1 to free dataptr, 0 to not free dataptr
 * Return: nada
 */
void free_list(list_t **head, int flag)
{
	list_t *walker = NULL;

	while (head && *head)
	{
		walker = *head;
		*head = (*head)->next;
		if (flag)
		{
			free(walker->key);
			free(walker->value);
		}
		free(walker);
	}
}


/**
 * delete_node_at_index - delete node at index
 * @head: head of linked list
 * @index: index of deletion
 *
 * Description: Function will take a linked list and delete node at index.
 * Return: 1 if successful, -1 if failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int listidx = 0;
	list_t *cur;
	list_t *prev;

	if (!*head)
		return (-1);
	cur = *head;
	prev = *head;

	while (listidx < index)
	{
		if (!cur)
			return (-1);
		if (listidx < index - 1)
			prev = prev->next;
		cur = cur->next;
		listidx++;
	}
	if (!index)
	{
		cur = cur->next;
		free(*head);
		*head = cur;
		return (1);
	}
	prev->next = cur->next;
	free(cur);
	return (1);
}
