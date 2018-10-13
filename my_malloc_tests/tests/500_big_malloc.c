#include <stdlib.h>
#include <string.h>

void	*malloc_use_mem(size_t size)
{
  void	*ptr = malloc(size);
  memset(ptr, 0, size);
  return (ptr);
}

int	main()
{
  void	*ptr;

  for (int i = 0; i < 500; i++)
    ptr =  malloc_use_mem(200000);
  return (0);
}
