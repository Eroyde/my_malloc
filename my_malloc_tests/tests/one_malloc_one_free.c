#include <stdlib.h>
#include <string.h>
int	main()
{
  char *string = malloc(40);
  memset(string, 0, 40);
  free(string);
  return (0);
}
