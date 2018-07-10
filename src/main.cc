#include <exception>

#include <game/Game.hh>
#include <debug/Debug.hh>
#include <tools/OptionsParser.hh>



int main(int ac, const char **av)
{
  // Options parsing
  OptionsParser opt(ac, av);
  try
  {
    opt.parse();
  }
  catch (const ArgumentsHelpVersionException&)
  {
    return EXIT_SUCCESS;
  }
  catch (const ArgumentsException& e)
  {
    ERROR("Invalid arguments:\n", e.what());
    return EXIT_FAILURE;
  }

  const auto replay = opt.optionExists("replay");
  const auto fullscreen = opt.optionExists("fullscreen");

  // Launch the game
  Game game(fullscreen);
  game.run(replay);

  return EXIT_SUCCESS;
}
