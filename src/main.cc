#include <common/Status.hh>
#include <core/Context.hh>
#include <game/Game.hh>
#include <common/Debug.hh>
#include <common/enums/modes.hh>


int main(int ac, const char **av)
{
  /// \todo use getopt, support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen(ac > 1);
  Context context(fullscreen);

  /// \todo do not push a flag, push a pointer to the mode itself
  Status::pushMode(e_mode::PLAYING); /// \todo main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
