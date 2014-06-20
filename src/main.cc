#include <common/include.hh>
#include <core/Context.hh>
#include <interface/Interface.hh>
#include <game/Game.hh>

auto g_status(std::make_unique<Status> ());
auto g_rm(std::make_unique<ResourcesManager> ("resources.xml"));
auto g_interface(std::make_unique<Interface> ());
auto g_window(std::make_unique<sf::RenderWindow> ());

int main(int ac, const char **av)
{
  bool fullscreen = false;

  PRINTF(av);

  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  if (ac > 1)
    fullscreen = true;

  Context context(fullscreen);
  context.init();

  g_status->pushMode(E_MODE_PLAYING); // TODO a main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
