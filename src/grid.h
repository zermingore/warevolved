#ifndef GRID_H_
# define GRID_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "struct_core.h"

cell	**grid_create(int c, int r, int size);
cell	**grid_add(int x, int y, cell *element, cell **grid);

#endif /* !GRID_H_ */
