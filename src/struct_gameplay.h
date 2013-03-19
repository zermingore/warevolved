#ifndef STRUCT_GAMEPLAY_H_
# define STRUCT_GAMEPLAY_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

struct	unit
{
  int	hp;
  int	x;
  int	y;
  int	clip;
  int	weapon;
  int	bleed;
  int	armor;
/* voices** voice */
/* textures** texture */
};

struct	backpack
{
  int	slots;
};

struct	army
{
  int	nb;
  int	color;
};

struct s_team
{
  int	useless;
  /* s_sound sound; */
};

#endif /* STRUCT_GAMEPLAY_H_ */
