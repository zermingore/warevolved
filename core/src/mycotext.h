#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct context *context;
struct		context
{
  char		*sprites[];
  SDL_Surface   *screen;
};

