#include <common/include.hh>
#include <core/Context.hh>
#include <interface/Interface.hh>
#include <game/Game.hh>

std::unique_ptr<Status> g_status(new Status());
std::unique_ptr<ResourcesManager> g_rm(new ResourcesManager("tst.xml"));
std::unique_ptr<Interface> g_interface(new Interface());


int main(int ac, const char **av)
{
  av = av;

  bool fullscreen = false;
  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  if (ac > 1)
    fullscreen = true;

  Context context(fullscreen);
  g_status->setWindow(context.init());
  g_status->pushMode(E_MODE_PLAYING); // TODO a main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
