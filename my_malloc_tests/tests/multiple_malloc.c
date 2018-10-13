#include <stdlib.h>
#include <string.h>

int	main()
{
  char *string = malloc(40);
  memset(string, 0, 40);
  char *string2 = malloc(100);
  memset(string2, 0, 100);
  char *string3 = malloc(4);
  memset(string3, 0, 4);
  char *string4 = malloc(30);
  memset(string4, 0, 30);
  char *string5 = malloc(29);
  memset(string5, 0, 29);
  char *string6 = malloc(47);
  memset(string6, 0, 47);
  char *string7 = malloc(876);
  memset(string7, 0, 876);
  char *string8 = malloc(234);
  memset(string8, 0, 234);
  char *string9 = malloc(2);
  memset(string9, 0, 2);
  return (0);
}
