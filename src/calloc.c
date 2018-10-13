/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Home-made calloc(3) implementation
*/

#include <string.h>
#include "malloc.h"

void	*calloc(size_t nb_elem, size_t elem_size)
{
	void	*pointer = NULL;

	ASSERT_RETURN(nb_elem != 0 && elem_size != 0, NULL);
	pointer = malloc(nb_elem * elem_size);
	ASSERT_RETURN(pointer != NULL, NULL);
	memset(pointer, 0, nb_elem * elem_size);
	return (pointer);
}