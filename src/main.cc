#include <common/include.hh>
#include <core/Context.hh>
#include <game/Game.hh>


int main(int ac, char **av)
{
  av = av; // FIXME

  bool fullscreen = false;
  if (ac > 1) // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
	fullscreen = true;

  Context* context = new Context(fullscreen);
  Game* game = new Game(context->init());

  game->run();


# ifdef DEBUG_LEAKS
  delete context;
  delete game;
# endif

  //delete[] g_filenames_units;

  return EXIT_SUCCESS;
}
