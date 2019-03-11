/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** malloc's functions
*/

#include "memlist.h"

t_memory *heap = NULL;

t_memory *heap_increase(t_memory *tmp, size_t size)
{
	t_memory *new = sbrk(0);

	if (sbrk(size + MEM_SIZE) == (void *)-1)
		return (NULL);
	new->size = size;
	new->free = 0;
	new->next = NULL;
	if (tmp) {
		tmp->next = new;
		new->prev = tmp;
	} else
		new->prev = NULL;
	return (new);
}

void heap_split(t_memory *tmp, size_t size)
{
	t_memory *new = (void *)tmp + size + MEM_SIZE;

	new->size = tmp->size - (size + MEM_SIZE);
	tmp->size = size;
	new->free = 1;
	tmp->free = 0;
	new->next = tmp->next;
	if (new->next)
		new->next->prev = new;
	tmp->next = new;
	new->prev = tmp;
}

t_memory *heap_last_block(void)
{
	t_memory *tmp = heap;
	t_memory *node = tmp;

	while (tmp) {
		node = tmp;
		tmp = tmp->next;
	}
	return (node);
}

t_memory *heap_nsized_block(size_t size)
{
	t_memory *tmp = heap;

	while (tmp && (tmp->size < (size + MEM_SIZE) || !tmp->free))
		tmp = tmp->next;
	return (tmp);
}

void *malloc(size_t size)
{
	size_t s = ALIGN(size);
	t_memory *tmp = heap_nsized_block(size);

	if (tmp)
		heap_split(tmp, s);
	else if (heap) {
		tmp = heap_last_block();
		tmp = heap_increase(tmp, s);
		if (!tmp)
			return (NULL);
	} else {
		tmp = heap_increase(tmp, (s < 2048) ? 2048 : s);
		if (!tmp)
			return (NULL);
		heap_split(tmp, s);
		heap = tmp;
	}
	return (tmp->data + 4);
}
