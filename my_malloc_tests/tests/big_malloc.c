#include <stdlib.h>
#include <string.h>

int	main()
{
  char *string = malloc(4000000);
  memset(string, 0, 4000000);
  return (0);
}
