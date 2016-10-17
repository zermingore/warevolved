#include <common/Status.hh>
#include <core/Context.hh>
#include <game/Game.hh>
#include <common/Debug.hh>
#include <common/enums/states.hh>


int main(int ac, const char **av)
{
  /// \todo use getopt, support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen(ac > 1);
  Context context(fullscreen);

  Status::pushState(e_state::PLAYING); /// \todo main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
