#ifndef DEBUG_H_
# define DEBUG_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include "structures.h"

void	debug_print_context(context c);
void	debug_print_grid(void **grid);

#endif /* !DEBUG_H_ */
