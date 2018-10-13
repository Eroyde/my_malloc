#include <stdlib.h>
#include <string.h>

int	main()
{
  char	*string;

  string = malloc(100);
  memset(string, 'a', 100);
  string[99] = '\0';

  char refstring[100];
  strcpy(refstring, string);
  
  string = realloc(string, 1000);

  if (strcmp(refstring, string) != 0)
    return 1;

  memset(string, 0, 1000);
  return 0;
}
