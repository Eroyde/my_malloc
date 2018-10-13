/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Home-made free(3) implementation
*/

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

static bool	break_free(my_malloc_block_t *start, my_malloc_block_t *end,
		size_t size)
{
	size_t	offset = 0;

	ASSERT_RETURN(end == NULL, false);
	ASSERT_RETURN(size >= (size_t)
		(__MY_MALLOC_PADDING__ * __MY_MALLOC_PAGESIZE__), false);
	offset = size - (size & (__MY_MALLOC_PAGESIZE__ - 1));
	size &= (__MY_MALLOC_PAGESIZE__ - 1);
	start->size = size;
	start->next = NULL;
	if (*get_free_list() == NULL || *get_free_list() > start
		|| (*get_free_list())->free == false)
		*get_free_list() = start;
	sbrk(- offset);
	return (true);
}

static void		block_fusion(my_malloc_block_t *block)
{
	size_t			new_size = block->size;
	my_malloc_block_t	*end = block, *start = block;

	if (block->next != NULL && block->next->free == true) {
		end = block->next;
		new_size += (end->size + sizeof(my_malloc_block_t));
	}
	if (block->prev != NULL && block->prev->free == true) {
		start = block->prev;
		new_size += (start->size + sizeof(my_malloc_block_t));
	}
	end = end->next;
	if (new_size == block->size || break_free(start, end, new_size) == true)
		return;
	start->next = end;
	start->size = new_size;
	if (end != NULL)
		end->prev = start;
	if (*get_free_list() == NULL || (*get_free_list())->free == false
		|| (*get_free_list())->size < new_size)
		*get_free_list() = start;
}

void	my_free(void *pointer)
{
	my_malloc_block_t	*block = __MY_MALLOC_FROM_MEMORY__(pointer);

	ASSERT_VOID(block->free == false);
	block->free = true;
	block_fusion(block);
}

void	free(void *pointer)
{
	ASSERT_VOID(pointer != NULL);
	pthread_mutex_lock(get_mutex());
	my_free(pointer);
	pthread_mutex_unlock(get_mutex());
}