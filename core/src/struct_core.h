#ifndef STRUCT_CORE_H_
# define STRUCT_CORE_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "structures.h"
/* #include "tools.h" */
/* #include "struct_core.h" */

/* typedef struct grid grid; */
/* typedef struct building building; */
/* typedef struct map map; */
typedef struct cell cell;
/* typedef struct terrain terrain; */

/* struct	map */
/* { */
/*   char	*grid; */
/* }; */

/* struct	grid */
/* { */
/*   int	w;/\* grid width *\/ */
/*   int	h;/\* grid height *\/ */
/*   cell	**c; */
/* }; */

struct	cell
{
  int	x;
  int	y;
  /* int	faction; */
  /* unit	unit; */
  /* int	discovered; /\* nb_factions bits *\/ */
  /* content */
};

/* struct  terrain */
/* { */
/*   int	type; */
/* }; */

/* struct	building */
/* { */
/*   int	type; */
/*   int	hp; */
/* }; */

#endif
