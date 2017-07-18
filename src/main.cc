#include <X11/Xlib.h> // to initialize the Xlib mutli-threads support
#include <core/Context.hh>
#include <game/Game.hh>
#include <debug/Debug.hh>
#include <tools/OptionsParser.hh>
#include <exception>



int main(int ac, const char **av)
{
  // Initialize the Xlib support for concurrent threads.
  XInitThreads(); /// \todo Explain why it cannot be in the Context

  try
  {
    OptionsParser p(ac, av);
  }
  catch (const ArgumentsHelpVersionException& e)
  {
    return 0;
  }
  catch (const ArgumentsException& e)
  {
    ERROR("Invalid arguments:", e.what());
    return 1;
  }
  catch (const std::exception& e)
  {
    ERROR("caught:", e.what());
    return 2;
  }
  catch (...)
  {
    ERROR("caught unexpected exception");
    return 3;
  }

  // 'argument parsing'
  /// \todo use an options parser, support: replay, resolution, ...
  auto replay(av && av[1] && av[1][0] == 'r');
  auto fullscreen(av && av[1] && av[1][0] == 'f');
  if (ac && replay)
  {
    NOTICE("Replay mode");
  }

  Context context(fullscreen);

  /// \todo main menu (pushState or the like)

  Game game;
  game.run(replay);

  return EXIT_SUCCESS;
}
