#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "structures.h"
#include "struct_core.h"
#include "init.h"
#include "grid.h"
#include "debug.h"

int		main(int argc, char *argv[])
{
  context	*c = NULL;
  cell		**grid = NULL;

  c = init(c);
  grid = grid_create(2, 2, sizeof(struct cell));

  if (grid == NULL)
    printf("ERROR : grid is NULL");

  printf("prgm name : %s\n", argv[0]);
  return (argc);
}
