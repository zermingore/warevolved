#include <common/include.hh>
#include <core/Context.hh>
#include <game/Game.hh>

int main(int ac, char **av)
{
  if (ac > 1) // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
	std::cout << av[0] << " does not support arguments, for now" << std::endl;

  Context* context = new Context(false); // bool: no full-screen
  Game* game = new Game(context->init());
  game->run();

# ifdef DEBUG_LEAKS
  delete context;
  delete game;
# endif

  return EXIT_SUCCESS;
}
