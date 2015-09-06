#include <common/Status.hh>
#include <core/Context.hh>
#include <game/Game.hh>
#include <common/Debug.hh>

///< log file definition
// std::ofstream* Debug::_log = new std::ofstream(LOG_FILENAME, std::ios_base::out | std::ios_base::app);

int main(int ac, const char **av)
{
  // Debug::initialize();
  // std::ofstream* log = new std::ofstream(LOG_FILENAME, std::ios_base::out | std::ios_base::app);
  // Debug::_log = log;


  // TODO use getopt -> support: resolution, graphic engine ({2,3}D, ASCII), ...
  PRINTF(av);

  bool fullscreen = ac > 1;
  Context context(fullscreen);

  // TODO: do not push a flag, push a pointer to the mode itself
  Status::pushMode(mode::PLAYING); // TODO main menu

  Game game;
  game.run();

  return EXIT_SUCCESS;
}
