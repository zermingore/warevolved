#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include "structures.h"
#include "error.h"
/* #include "debug.h" */
/* #include "tools.h" */
#include "struct_core.h"

cell	**grid_create(int c, int r, int size)
{
  int	i;
  cell  **grid;

  grid = malloc(c * size);
  for (i = 1; i <= r; i++)
    grid[i] = malloc (c * size);

  return(grid);
}

cell	**grid_add(int x, int y, cell *element, cell **grid)
{
  if ((grid == NULL) || (element == NULL))
  {
    error_argument("grid_add : element and/or pgrid are NULL");
    return(NULL);
  }

  /* if (pgrid[x][y] == NULL) */
    /* printf("grid NULL %p", pgrid[x][y]); */

  grid[x][y] = *element;
  /* memcpy(pgrid[x][y], element, size); */
  return (0);
}
