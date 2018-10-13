#include <stdlib.h>
#include <string.h>

int	main()
{
  void	*ptr = malloc(1000);
  void	*save = ptr;
  memset(ptr, 0, 1000);
  free(ptr);
  ptr = malloc(1000);
  if (ptr != save)
    return (1);
  return (0);
}
