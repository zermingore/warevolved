#include <core/Context.hh>
#include <common/System.hh>
#include <common/Settings.hh>
#include <graphics/GraphicsEngine.hh>


Context::Context(bool fullscreen)
{
  if (fullscreen)
    Settings::initialize(24, 8, 4);
  else
    Settings::initialize(0, 0, 0); // vanilla (debug) mode

  Settings::setFullScreen(fullscreen);
  _system = std::make_unique<System> (2, 1); // SFML version: 2.1
  init();
}


void Context::init()
{
# ifdef DEBUG
  if (_system->sfmlMajor() < 2)
    std::cerr << "SFML version not officially supported" << std::endl;
# endif

  sf::ContextSettings contextSettings(Settings::depth(),
                                      Settings::stencil(),
                                      Settings::antiAliasing(),
                                      _system->sfmlMajor(),
                                      _system->sfmlMinor());

  // getting right resolution, from desktop
  std::unique_ptr<sf::RenderWindow> window;
  if (Settings::fullScreen())
  {
    window = std::make_unique<sf::RenderWindow> (sf::VideoMode::getDesktopMode(),
                                                 "War Evolved",
                                                 sf::Style::Fullscreen);
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

    window  = std::make_unique<sf::RenderWindow> (video_mode, "War Evolved");
  }

# ifndef DEBUG_PERFS
  window->setFramerateLimit(60);
# else
  window->setFramerateLimit(0);
#endif
  //_window->setIcon(64, 64, "icon");

  graphics::GraphicsEngine::setWindow(std::move(window));

  // Deducing some Status
  graphics::GraphicsEngine::setCellWidth(64); // TODO change dynamically (in px)
  graphics::GraphicsEngine::setCellHeight(64); // TODO change dynamically (in px)
  graphics::GraphicsEngine::setGridThickness(5); // TODO change dynamically (in px)
}
