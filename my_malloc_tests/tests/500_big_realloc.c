#include <stdlib.h>
#include <string.h>

int	realloc_time()
{
  char	*string;

  string = malloc(100);
  memset(string, 'a', 100);
  string[99] = '\0';

  char refstring[100];
  strcpy(refstring, string);
  
  string = realloc(string, 1000000);

  if (strcmp(refstring, string) != 0)
    return 1;

  memset(string, 0, 1000000);
  free(string);
  return 0;
}

int	main()
{
  for (int i = 0; i < 500; i++) {
    if (realloc_time() != 0)
      return 1;
  }
  return 0;
}
