/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Function to display internal representation of malloc data
*/

#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

void	show_alloc_mem(void)
{
	my_malloc_block_t	*block = *get_metadata();

	fflush(stdout);
	fprintf(stderr, "break : 0x%lX\n", (size_t)sbrk(0));
	while (block != NULL) {
		if (block->free == false)
			fprintf(stderr, "0x%lX - 0x%lX : %lu bytes\n",
				(size_t)block + sizeof(my_malloc_block_t),
				(size_t)block + sizeof(my_malloc_block_t)
					+ block->real_size,
				block->real_size);
		block = block->next;
	}
	fflush(stdout);
}