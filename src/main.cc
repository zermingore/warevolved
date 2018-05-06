#include <exception>

#include <game/Game.hh>
#include <debug/Debug.hh>
#include <tools/OptionsParser.hh>



int main(int ac, const char **av)
{
  // Options parsing
  auto fullscreen = false;
  auto replay = false;
  try
  {
    OptionsParser p(ac, av);
    replay = p.optionExists("replay");
    fullscreen = p.optionExists("fullscreen");
  }
  catch (const ArgumentsHelpVersionException&)
  {
    return EXIT_SUCCESS;
  }
  catch (const ArgumentsException& e)
  {
    ERROR("Invalid arguments:", e.what());
    return EXIT_FAILURE;
  }

  // Launch the game
  Game game(fullscreen);
  game.run(replay);

  return EXIT_SUCCESS;
}
