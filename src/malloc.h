/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Header definition of my_malloc
*/

#pragma once

#include <stddef.h>
#include <pthread.h>
#include <stdbool.h>

// Memory alignment
#define __MY_MALLOC_PADDING__		8

// Magic number defining the number of pages from pagesize
#define __MY_MALLOC_NB_PAGES__		8


// Pagesize needed to alloc as fast as the CPU allows
#define __MY_MALLOC_PAGESIZE__		sysconf(_SC_PAGESIZE)

// This aligns addresses. You're not expected to understand this.
#define __MY_MALLOC_ALIGN__(x, y)	(((x) + (y) - 1) &~ ((y) - 1))

// Size to pass to sbrk
#define __MY_MALLOC_TO_ALLOC__(size)	__MY_MALLOC_ALIGN__((size)	\
					+ sizeof(my_malloc_block_t),	\
					__MY_MALLOC_NB_PAGES__ *	\
					__MY_MALLOC_PAGESIZE__);

// Accessing the allocated memory from the block
#define	__MY_MALLOC_MEMORY__(block)	((void *)((size_t)(block) +	\
					sizeof(my_malloc_block_t)))

// Accessing the block from allocated memory
#define __MY_MALLOC_FROM_MEMORY__(pointer)	(my_malloc_block_t *)	\
						((size_t)(pointer) -	\
						sizeof(my_malloc_block_t))

// Assert definition for cleaner code
#define ASSERT_RETURN(x, y)		if (!(x)) { return (y); }
#define ASSERT_VOID(x)			if (!(x)) { return; }

// Block structure
typedef struct				my_malloc_block_s
{
	size_t				real_size;
	size_t				size;
	struct my_malloc_block_s	*next;
	struct my_malloc_block_s	*prev;
	bool				free;
}					my_malloc_block_t;

// Mutex for thread safety
pthread_mutex_t		*get_mutex(void);

// First block needed to browse list of used blocks
my_malloc_block_t	**get_metadata(void);

// First block needed to browse list of free blocks
my_malloc_block_t	**get_free_list(void);

// Standard (re-)definitions of standard library
void	*malloc(size_t size);
void	free(void *pointer);
void	*relloc(void *pointer, size_t size);
void	*calloc(size_t nb_elem, size_t size_elem);

// Internal functions without mutexes to not cause deadlock
void	my_free(void *pointer);
void	*my_malloc(size_t size);

// Displays an internal representation of the malloc's memory for debugging
void	show_alloc_mem(void);

// Just internal functions
void	split_block(my_malloc_block_t *block, size_t size);
void	*get_new_block(my_malloc_block_t *block, size_t size, size_t real_size);
