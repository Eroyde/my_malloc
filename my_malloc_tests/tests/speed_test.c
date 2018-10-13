#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <unistd.h>

void show_alloc_mem();

void	*ptr_alloc(size_t size)
{
  void	*ptr = malloc(size);
  return (ptr);
}

int	main()
{
  void	*brkpt = sbrk(0);
  void	*ptr[50000];
  clock_t start = clock(), diff;

  for (int i = 0; i < 50000; i++)
    ptr[i] = ptr_alloc(100);

  for (int i = 0; i < 50000; i++) {
    memset(ptr[i], 0, 100);
  }

  for (int i = 0; i < 50000; i++)
    free(ptr[i]);

  diff = clock() - start;
  uint timer = diff * 1000 / CLOCKS_PER_SEC;

  void	*brkpt2 = sbrk(0);
  ptrdiff_t ramusage = brkpt2 - brkpt;

  printf("\t\t\t%u milliseconds\n\t\t\t%td KB used\n", timer, ramusage / 1000);
}
