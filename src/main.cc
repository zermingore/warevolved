#include <common/include.hh>
#include <core/Context.hh>
#include <interface/Interface.hh>
#include <game/Game.hh>

Status *g_status = new Status();
ResourcesManager *g_rm = new ResourcesManager("tst.xml");
Interface *g_interface = new Interface();


int main(int ac, const char **av)
{
  av = av; // FIXME use getopt

  bool fullscreen = false;
  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  if (ac > 1)
    fullscreen = true;

  Context *context = new Context(fullscreen);
  g_status->setWindow(context->init());
  g_status->pushMode(E_MODE_PLAYING); // TODO a main menu
  Game *game = new Game();
  game->run();

# ifdef DEBUG_LEAKS
  delete context;
  delete game;
  delete g_status;
  delete g_rm;
  delete g_interface;
# endif

  return EXIT_SUCCESS;
}
