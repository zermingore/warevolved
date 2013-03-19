#ifndef ERROR_H_
# define ERROR_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	error_sdl_init()
{
  if ((write(STDERR_FILENO, "SDL_Init failure\n", 17)) == 0)
    printf("SDL_Init failure\nwrite error\n");
  return (-1);
}

int	error_malloc(char *msg)
{
  if ((write(STDERR_FILENO, "Malloc Failure\n", 15)) == 0)
    printf("Malloc Failure\nWrite error\n");
  printf("error msg : %s\n", msg);
  return (-1);
}

int	error_argument(char *msg)
{
  if ((write(STDERR_FILENO, "Parameter Failure\n", 18)) == 0)
    printf("Parameter Failure\nwrite error\n");
  printf("error msg : %s\n", msg);
  return (-1);
}

#endif /* !ERROR_H_ */
