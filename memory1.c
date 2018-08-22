#include "memory.h"

/**
 * _realloc - reallocates more memory
 * @ptr: pointer to the allocated memory
 * @old_size: current size of ptr
 * @new_size: new size
 * Return: pointer to the newly malloc'd space
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size,
	       list_t **mt)
{
	unsigned int i;
	char *new_array, *tmp;

	if (new_size == old_size)
		return (ptr);
	if (!ptr)
	{
		tmp = malloc(new_size);
		add_node(mt, (void *)tmp);
		return (tmp);
	}

	if (!new_size && ptr)
		return (0);

	new_array = malloc(new_size);
	add_node(mt, (void *)new_array);
	reset_buffer(new_array, new_size);

	if (new_array)
	{
		for (i = 0; i < new_size; i++)
			new_array[i] = *((char *) ptr + i);
	}
	return ((void *) new_array);
}

/**
 * reset_buffer - sets all the elements of a malloc'd space to 0
 * @buffer: pointer to the malloc'd space
 * @buf_size: size of the buffer
 * Return: nothing
 */
void reset_buffer(char *buffer, ssize_t buf_size)
{
	ssize_t i = 0;

	while (i < buf_size)
		buffer[i++] = '\0';
}

void freememtracker(list_t **mt)
{
	list_t *walker = NULL;

        while (mt && *mt)
        {
                walker = *mt;
                *mt = (*mt)->next;
		free(walker->dataptr);
                free(walker);
        }
}
