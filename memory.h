#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdlib.h>

/**
 * struct alloc_s - singly linked list of malloc'd stuff
 * @addr: pointer to addr
 * @next: struct alloc_s ptr to the next node
 *
 * Description: singly linked list used to hold malloc'd stuff
 */
typedef struct alloc_s
{
	void *addr;
	struct alloc_s *next;
} alloc_t;

void reset_buffer(char *buffer, ssize_t buf_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif
