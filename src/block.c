/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Block manipulation functions
*/

#include <unistd.h>
#include <string.h>
#include "malloc.h"

static void	*new_block_from_old(my_malloc_block_t *block, size_t size)
{
	size_t			block_size = ((block->size >= size)
		? size : block->size);
	my_malloc_block_t	*new_block = my_malloc(size);

	ASSERT_RETURN(new_block != NULL, NULL);
	block = __MY_MALLOC_MEMORY__(block);
	memcpy(new_block, block, block_size);
	my_free(block);
	return (new_block);
}

static void	*make_block_bigger(my_malloc_block_t *block, size_t size)
{
	size_t	alloc_size = 0;

	if (size < block->size)
	{
		block->size = size;
		brk(block + sizeof(my_malloc_block_t) + size);
	} else {
		alloc_size = __MY_MALLOC_TO_ALLOC__(size);
		ASSERT_RETURN(sbrk(alloc_size) != (void *)-1, NULL);
		block->size = alloc_size - sizeof(my_malloc_block_t);
		split_block(block, size);
	}
	return (__MY_MALLOC_MEMORY__(block));
}

static void	*fuse_next_block(my_malloc_block_t *block,
		my_malloc_block_t *next, size_t size)
{
	if (*get_free_list() == next)
		*get_free_list() = NULL;
	block->size += (next->size + sizeof(my_malloc_block_t));
	block->next = next->next;
	if (next->next != NULL)
		next->next->prev = block;
	split_block(block, size);
	return (__MY_MALLOC_MEMORY__(block));
}

void		*get_new_block(my_malloc_block_t *block, size_t size,
		size_t real_size)
{
	void			*allocated_memory = NULL;
	my_malloc_block_t	*next = block->next;

	if (next == NULL)
		allocated_memory = make_block_bigger(block, size);
	else if (next->free == true
		&& next->size + block->size + sizeof(my_malloc_block_t) >= size)
		allocated_memory = fuse_next_block(block, next, size);
	else
		allocated_memory = new_block_from_old(block, size);
	if (allocated_memory != NULL)
		(__MY_MALLOC_FROM_MEMORY__(allocated_memory))->real_size
			= real_size;
	return (allocated_memory);
}

void		split_block(my_malloc_block_t *block, size_t size)
{
	my_malloc_block_t	*new_block = (my_malloc_block_t *)
		((size_t)block + size + sizeof(my_malloc_block_t));
	my_malloc_block_t	*next = block->next;

	if (block->size > __MY_MALLOC_ALIGN__
	(size + sizeof(my_malloc_block_t), __MY_MALLOC_PADDING__)) {
		new_block->next = next;
		new_block->prev = block;
		new_block->size = block->size - size
			- sizeof(my_malloc_block_t);
		if (next != NULL)
			next->prev = new_block;
		new_block->free = true;
		block->size = size;
		block->next = new_block;
		if (*get_free_list() == NULL
			|| (*get_free_list())->free == false
			|| (*get_free_list())->size < new_block->size)
			*get_free_list() = new_block;
	}
}