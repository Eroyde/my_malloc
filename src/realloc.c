/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Home-made realloc(3) implementation
*/

#include "malloc.h"

static void	*my_realloc(void *pointer, size_t real_size)
{
	size_t			size = __MY_MALLOC_ALIGN__
				(real_size, __MY_MALLOC_PADDING__);
	my_malloc_block_t	*block = __MY_MALLOC_FROM_MEMORY__(pointer);
	void			*allocated_memory;

	if (size == block->size)
		allocated_memory = pointer;
	else
		allocated_memory = get_new_block(block, size, real_size);
	return (allocated_memory);
}

void	*realloc(void *pointer, size_t size)
{
	void	*new_pointer = NULL;

	ASSERT_RETURN(pointer != NULL, malloc(size));
	if (size == 0) {
		free(pointer);
		new_pointer = malloc(size);
	} else {
		pthread_mutex_lock(get_mutex());
		new_pointer = my_realloc(pointer, size);
		pthread_mutex_unlock(get_mutex());
	}
	return (new_pointer);
}