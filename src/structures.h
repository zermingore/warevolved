#ifndef STRUCTURES_H_
# define STRUCTURES_H_
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>


typedef	struct context context; /* */
typedef struct input input;
typedef struct element *element;
typedef element *linked_list;

struct		element
{
  int		value;
  element	*next;
};

struct		linked_list
{
  element	*list;
};

struct		context
{
  SDL_Surface	*screen;
  input		*in;
};

struct	input
{
  char	keys[SDLK_LAST];
  char	mouse[5];
  int	mouse_x;
  int	mouse_y;
};

#endif /* !STRUCTURES_H_ */
