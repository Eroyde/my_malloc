#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void	*alloc_mem()
{
  char	*ptr = malloc(1000);
  memset(ptr, 'a', 1000);
  free(ptr);
  usleep(1000);
  ptr = malloc(10);
  memset(ptr, 'a', 10);
  free(ptr);
  return (ptr);
}

int	main()
{
  int nbthreads = 200;
  pthread_t thread[nbthreads];
  
  for (int i = 0; i < nbthreads; i++)
    pthread_create(&thread[i], NULL, &alloc_mem, NULL);
  
  for (int i = 0; i < nbthreads; i++)
    pthread_join(thread[i], NULL);
  return (0);
}
