#include <core/Context.hh>
#include <game/Game.hh>
#include <common/Debug.hh>

#include <stdio.h>

int main(int ac, const char **av)
{
  /// \todo use getopt, support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen(ac > 1);
  Context context(fullscreen);

  /// \todo main menu (pushState or the like)

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
