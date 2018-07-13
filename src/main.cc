#include <exception>

#include <game/Game.hh>
#include <debug/Debug.hh>
#include <tools/options/OptionsParser.hh>



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

  // Launch the game
  Game game(opt);
  game.run();

  return EXIT_SUCCESS;
}
