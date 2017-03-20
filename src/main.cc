#include <core/Context.hh>
#include <game/Game.hh>
#include <debug/Debug.hh>


int main(int ac, const char **av)
{
  /// \todo use getopt, support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  auto fullscreen(ac > 1);
  Context context(fullscreen);

  /// \todo main menu (pushState or the like)

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
