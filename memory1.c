#include "memory.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new_array;

	if (new_size == old_size)
		return (ptr);
	
	if (!ptr)
	{
		free(ptr);
		return (malloc(new_size));
	}

	if (!new_size && ptr)
	{
		free(ptr);
		return (0);
	}

	new_array = malloc(new_size);
	reset_buffer(new_array, new_size);

	if (new_array)
	{
		for (i = 0; i < new_size; i++)
			new_array[i] = *((char *) ptr + i);
	}
	
	free(ptr);
	return ((void *) new_array);
}

void reset_buffer(char *buffer, ssize_t buf_size)
{
	ssize_t i = 0;

	while (i < buf_size)
		buffer[i++] = '\0';
}
