/** \mainpage War Evolved
 * War Evolved is a simple 2D tactical RPG\n
 * https://github.com/zermingore/warevolved\n
 * Please report any bug, feature request, ...
 *
 * \file
 * \date September 15 2010
 * \author Zermingore
 * \brief Entry point
 */

#include <debug/Debug.hh>
#include <game/Game.hh>
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
