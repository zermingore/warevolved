#include <core/Context.hh>
#include <common/System.hh>
#include <common/Settings.hh>
#include <common/globals.hh>

std::unique_ptr<Settings> g_settings;

Context::Context(bool fullscreen)
{
  if (fullscreen)
    g_settings = std::make_unique<Settings> (24, 8, 4);
  else
    g_settings = std::make_unique<Settings> (0, 0, 0); // vanilla (debug) mode

  g_settings->setFullScreen(fullscreen);
  _system.reset(new System(2, 1)); // SFML version: 2.1
  init();
}


void Context::init()
{
# ifdef DEBUG
  if (_system->sfmlMajor() < 2)
    std::cerr << "SFML version not officially supported" << std::endl;
# endif

  sf::ContextSettings contextSettings(g_settings->depth(),
                                      g_settings->stencil(),
                                      g_settings->antiAliasing(),
                                      _system->sfmlMajor(),
                                      _system->sfmlMinor());

  // getting right resolution, from desktop
  if (g_settings->fullScreen())
  {
    g_window.reset(new sf::RenderWindow(sf::VideoMode::getDesktopMode(),
                                       "War Evolved",
                                       sf::Style::Fullscreen));
  }
  else
  {
    sf::VideoMode video_mode;
    video_mode.width = 800;
    video_mode.height = 600;
    video_mode.bitsPerPixel = 32;

    if (!video_mode.isValid())
    {
      std::cerr << "Unsupported Video Mode, falling back" << std::endl;
      video_mode = sf::VideoMode::getDesktopMode(); // falling back to desktop mode
      if (!video_mode.isValid())
        std::exit(-1); // This time we quit // TODO browse all supported modes
    }

    g_window.reset(new sf::RenderWindow(video_mode, "War Evolved"));
  }

# ifndef DEBUG_PERFS
  g_window->setFramerateLimit(60);
# else
  g_window->setFramerateLimit(0);
#endif
  //_window->setIcon(64, 64, "icon");

  // Deducing some Status
  g_status->setCellWidth(64); // TODO change dynamically (in px)
  g_status->setCellHeight(64); // TODO change dynamically (in px)
  g_status->setGridThickness(5); // TODO change dynamically (in px)
}
