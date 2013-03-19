#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "../headers/context.h"

/* create context and return a pointer on it */

int	load_all(context c)
{
  int	i;
  char	*all[] = {"sprite.bmp"};

  c->nb_sprites = sizeof(all) / sizeof(char*);
  c->images = malloc(c->nb_sprites * sizeof(SDL_Surface*));
  for(i = 0; i < c->nb_sprites; i++)
  {
    c->sprites[i] = SDL_LoadBMP(all[i]);
    SDL_SetColorKey(c->sprites[i], SDL_SRCCOLORKEY, SDL_MapRGBA(c->sprites[i]->format, 255, 255, 255, 0));
  }

  return (0);
}


int	init(context *c, int x, int y)
{
  if ((c == NULL) || (SDL_Init(SDL_INIT_VIDEO) != 0))
    return (-1);
  c->x = x;
  c->y = y;
  c->nb_sp = NB_SPRITES;
  c->screen = SDL_SetVideoMode(c->XRES, c->YRES, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_ShowCursor(0);
  if ((c->screen == NULL) || (load_all(c) != 0) || (init_sprites(c) != 0))
    return (-1);

  return (0);
}

int	release(context *c)
{
  int	i;

  for(i = 0; i < c->nb_img; i++)
    SDL_FreeSurface(c->images[i]);
  free(c->images);
  free(c->sprites);
  SDL_Quit();

  return (0);
}


int	        main(int argc,char** argv)
{
  context	c;
  input		in;
  unsigned int	elapsed;
  unsigned int	lasttime = SDL_GetTicks();

  memset(&in, 0, sizeof(in));  // Instanciation d'une structure Input, et initialisation : tous les champs à 0.
  if (init(&c, 400, 300, 10) != 0)   // init en 800*600 avec 10 sprites
    return (-1);
  while(!in.key[SDLK_ESCAPE] && !in.quit)
  {
    UpdateEvents(&in);
    Evolue(&c, &in);
    while(SDL_Flip(c.screen) != 0)  /* wait for graphic card */
      SDL_Delay(1);

    elapsed = SDL_GetTicks() - lasttime;
    if (elapsed < 20) /* 50 FPS (20*50 = 1000) */
      SDL_Delay(20 - elapsed);
  }
  release(&c);

  return (0);
}

