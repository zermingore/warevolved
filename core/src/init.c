# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include "structures.h"
# include "init.h"
# include "error.h"
/* # include "debug.h" */

context	*init(context *c)
{
  input	in;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    error_sdl_init();

  c = malloc(sizeof (struct context));
  if (c == NULL)
    error_malloc("init : c is NULL");

  c->screen = SDL_SetVideoMode(280, 124, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  c->in = memset(&in, 0, sizeof(in));

  /* debug_print_context(c); */
  return (c);
}
