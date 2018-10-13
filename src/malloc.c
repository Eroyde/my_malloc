/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Home-made malloc(3) implementation
*/

#include <unistd.h>
#include "malloc.h"

static void	*request_new_block(my_malloc_block_t *last_block,
	size_t size, bool free)
{
	size_t			alloc_size = __MY_MALLOC_TO_ALLOC__(size);
	my_malloc_block_t	*block = sbrk(alloc_size);

	ASSERT_RETURN(block != (void *)-1, NULL);
	if (last_block != NULL)
		last_block->next = block;
	block->size = alloc_size - sizeof(my_malloc_block_t);
	block->free = free;
	block->prev = last_block;
	block->next = NULL;
	if (last_block != NULL)
		split_block(block, size);
	return (__MY_MALLOC_MEMORY__(block));
}

static void	*search_for_space(size_t size)
{
	my_malloc_block_t	*last = NULL;
	my_malloc_block_t	*block = *get_metadata();

	if (*get_free_list() != NULL
		&& (*get_free_list())->free == true
		&& (*get_free_list())->size >= size) {
		block = *get_free_list();
		(*get_free_list())->free = false;
		split_block(*get_free_list(), size);
		return (__MY_MALLOC_MEMORY__(block));
	}
	while (block != NULL) {
		if (block->free == true && block->size >= size) {
			block->free = false;
			split_block(block, size);
			return (__MY_MALLOC_MEMORY__(block));
		}
		last = block;
		block = block->next;
	}
	return (request_new_block(last, size, false));
}

void	*my_malloc(size_t real_size)
{
	size_t	size = __MY_MALLOC_ALIGN__(real_size, __MY_MALLOC_PADDING__);
	void	*allocated_memory = NULL;

	if (*get_metadata() == NULL)
		*get_metadata() = request_new_block(NULL, size, true);
	ASSERT_RETURN(*get_metadata() != NULL, NULL);
	allocated_memory = search_for_space(size);
	if (allocated_memory != NULL)
		((my_malloc_block_t *)
			(allocated_memory - sizeof(my_malloc_block_t)))
			->real_size = real_size;
	return (allocated_memory);
}

// Wrapper of malloc with thread safety
void	*malloc(size_t size)
{
	void    *pointer = NULL;

	pthread_mutex_lock(get_mutex());
	pointer = my_malloc(size);
	pthread_mutex_unlock(get_mutex());
	return (pointer);
}