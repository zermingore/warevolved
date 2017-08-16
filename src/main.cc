#include <core/Context.hh>
#include <X11/Xlib.h> // to initialize the Xlib mutli-threads support
#include <game/Game.hh>
#include <debug/Debug.hh>
#include <tools/OptionsParser.hh>
#include <exception>



int main(int ac, const char **av)
{
  // Initialize the Xlib support for concurrent threads.
  XInitThreads(); /// \todo Explain why it cannot be in the Context

  // Options parsing
  auto fullscreen = false;
  auto replay = false;
  try
  {
    OptionsParser p(ac, av);
    replay = p.optionExists("replay");
    fullscreen = p.optionExists("fullscreen");
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


  Context context(fullscreen);

  /// \todo main menu (pushState or the like)

  Game game;
  game.run(replay);

  return EXIT_SUCCESS;
}
