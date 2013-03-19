#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "structures.h"
#include "struct_core.h"
#include "init.h"
#include "error.h"

void	debug_print_context(context *c)
{
  int	i = 0;

  if (c != NULL)
  {
    printf("\t..:PRINTING KEYS ARRAY:..\n");
    for(i = 1; i < SDLK_LAST; i++)
    {
      printf("trying to access %i : ", i);
      printf("%i\n", c->in->keys[i]);
    }
    printf("\t..:PRINTING MOUSE ARRAY:..\n");
    for (i = 0; i < 5; i++)
      printf("%i; ", c->in->mouse[i]);
    printf("\n");
    printf("mouse_x is now : %i\n", c->in->mouse_x);
    printf("mouse_y is now : %i\n", c->in->mouse_y);
  }
  else
    error_argument("debug_print_context : c is NULL");
}


void	debug_print_grid(void **grid)
{
  int	i, j;
  int	r, c; /* grepme */
  int	***g = *grid;

  r = 2; c = 2;

  printf("\tgrid[COLUMN][ROW]\n");
  for (i = 1; i <= c; i++)
    for (j = 1; j <= r; j++)
      printf("grid[%i][%i] = %i\n", i, j, *g[i][j]);
}
