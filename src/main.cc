#include <common/include.hh>
#include <core/Context.hh>
#include <core/Game.hh>


int main(int ac, char **av)
{
  if (ac > 1) // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ascii), ...
	std::cout << "not supporting arguments, for now" << std::endl;

  Context* context = new Context(false);

  Game* game = new Game(context->init());
  game->run();

  return EXIT_SUCCESS;
}
