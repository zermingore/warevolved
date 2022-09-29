/** \mainpage War Evolved
 * War Evolved is a simple 2D tactical RPG\n
 * Repository URL: https://sr.ht/~jp_foss/war_evolved/\n
 * Please report any bug, feature request, ...
 * at: https://todo.sr.ht/~jp_foss/war_evolved
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
  Debug::init();

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
