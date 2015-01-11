#include <common/include.hh>
#include <core/Context.hh>
#include <interface/Interface.hh>
#include <game/Game.hh>


std::unique_ptr<Status> g_status(std::make_unique<Status> ());
std::unique_ptr<ResourcesManager> g_rm(std::make_unique<ResourcesManager> ("resources.xml"));
std::unique_ptr<Interface> g_interface(std::make_unique<Interface> ());
std::unique_ptr<sf::RenderWindow> g_window(std::make_unique<sf::RenderWindow> ());
std::unique_ptr<Text> g_text(std::make_unique<Text> ());


int main(int ac, const char **av)
{
  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen = ac > 1;
  Context context(fullscreen);
  g_status->pushMode(E_MODE_PLAYING); // TODO a main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
