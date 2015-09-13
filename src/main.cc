#include <common/Status.hh>
#include <core/Context.hh>
#include <game/Game.hh>
#include <common/Debug.hh>


int main(int ac, const char **av)
{
  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen = ac > 1;
  Context context(fullscreen);

  // TODO: do not push a flag, push a pointer to the mode itself
  Status::pushMode(mode::PLAYING); // TODO main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
