/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** heap struct
*/

#pragma once
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

# define ALIGN(x) ((((x - 1) >> 3) << 3) + 8)
# define INVALID_ADR ((void *) - 1)
# define MEM_SIZE (32)

typedef struct	s_memory
{
	struct s_memory *next;
	struct s_memory *prev;
	size_t size;
	int free;
	char data[4];
}		t_memory;

t_memory *get_addr(void *);
void heap_reduct_brk(t_memory *);
void heap_merge_block(t_memory *);
void free(void *);
t_memory *heap_increase(t_memory *, size_t);
void heap_split(t_memory *, size_t);
t_memory *heap_last_block(void);
t_memory *heap_nsized_block(size_t);
void *malloc(size_t);
