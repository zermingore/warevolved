#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

typedef struct sprite *sprite;
struct sprite
{
  int	index;
  int	x, y;
};

typedef struct context *context;
struct context
{
  SDL_Surface*	screen;
  SDL_Surface**	textures;
  int		nb_textures;
  int		x, y;
};


typedef struct input *input;
struct input
{
  char	key[SDLK_LAST];
  int	mousex, mousey;
  char	mousebuttons[5];
  char	quit;
};

