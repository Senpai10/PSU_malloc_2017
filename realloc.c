/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** realloc's functions
*/

#include <string.h>
#include "memlist.h"

void *get_ptr(t_memory *block)
{
	return ((void *)block);
}

void *alloc_and_copy(t_memory *origin, size_t size)
{
	void *oldptr;
	void *newptr = malloc(size);

	oldptr = get_ptr(origin);
	memcpy(newptr, oldptr, (size < origin->size ? size : origin->size));
	return (newptr);
}

void *realloc(void *ptr, size_t size)
{
	t_memory *origin = heap;
	t_memory *block = get_addr(ptr);
	void *newptr;

	if (size == 0) {
		free(ptr);
		return (NULL);
	}
	while (origin != NULL) {
		if (origin == block) {
			free(ptr);
			return (alloc_and_copy(origin, size));
		}
		origin = origin->next;
	}
	return (newptr = malloc(size));
}
