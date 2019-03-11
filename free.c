/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** free's functions
*/

#include "memlist.h"
#include <stdio.h>

t_memory *get_addr(void *ptr)
{
	return ((t_memory *)ptr - 1);
}

void heap_reduct_brk(t_memory *block)
{
	if (!block->next) {
		if (block->prev)
			block->prev->next = NULL;
		else
			block = NULL;
		brk(block);
	}
}

void heap_merge_block(t_memory *block)
{
	if (block->prev && block->prev->free) {
		block->prev->size += block->size + MEM_SIZE;
		block->prev->next = block->next;
		block = block->prev;
		if (block->next)
			block->next->prev = block;
		if (block->next &&  block->next->free)
			heap_merge_block(block->next);
	} else if (block->next && block->next->free) {
		block->size += block->next->size + MEM_SIZE;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	} else
		heap_reduct_brk(block);
}

void free(void *ptr)
{
	t_memory *tmp = heap;
	t_memory *addr = get_addr(ptr);

	while (tmp && tmp != addr)
		tmp = tmp->next;
	if (tmp) {
		addr->free = 1;
		heap_merge_block(addr);
	}
}
