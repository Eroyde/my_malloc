/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Metadata used by malloc, abusing statics for globals because Epitech
*/

#include <stdio.h>
#include "malloc.h"

my_malloc_block_t	**get_metadata(void)
{
	static my_malloc_block_t	*my_malloc_metadata = NULL;

	return (&my_malloc_metadata);
}

my_malloc_block_t	**get_free_list(void)
{
	static my_malloc_block_t	*my_malloc_free = NULL;

	return (&my_malloc_free);
}

pthread_mutex_t		*get_mutex(void)
{
	static pthread_mutex_t	my_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&my_malloc_mutex);
}