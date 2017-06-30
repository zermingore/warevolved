#include <X11/Xlib.h> // to initialize the Xlib mutli-threads support
#include <core/Context.hh>
#include <game/Game.hh>
#include <debug/Debug.hh>



int main(int ac, const char **av)
{
  // Initialize the Xlib support for concurrent threads.
  XInitThreads(); /// \todo don't really know why it cannot be in the Context

  /// \todo use getopt, support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool replay = false; // (av && av[1] && av[1][0] == 'r');

  auto fullscreen(ac > 1);
  Context context(fullscreen);

  /// \todo main menu (pushState or the like)

  Game game;
  game.run(replay);

  return EXIT_SUCCESS;
}
