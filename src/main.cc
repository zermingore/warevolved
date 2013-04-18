#include <common/include.hh>
#include <core/Context.hh>
#include <game/Game.hh>


int main(int ac, char **av)
{
  if (ac > 1) // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ascii), ...
	std::cout << av[0] << " does not support arguments, for now" << std::endl;

  Context* context = new Context(false); // bool: no fullscreen

  Game* game = new Game(context->init());
  game->run();

  return EXIT_SUCCESS;
}
