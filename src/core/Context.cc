#include <core/Context.hh>

#include <config/Settings.hh>
#include <graphics/GraphicsEngine.hh>
#include <debug/Debug.hh>



Context::Context(const bool fullscreen)
  : _system(std::make_unique<System> (2, 1)) // SFML version: 2.1
  , _settings(std::make_shared<Settings> ())
{
  _settings->setFullScreen(fullscreen);
  init();
}


void Context::init()
{
  if (_system->sfmlMajor() < 2)
  {
    ERROR("SFML version not officially supported");
    assert(!"SFML version not supported, aborting in debug");
  }

  sf::ContextSettings contextSettings(_settings->depth(),
                                      _settings->stencil(),
                                      _settings->antiAliasing(),
                                      _system->sfmlMajor(),
                                      _system->sfmlMinor());

  // getting right resolution, from desktop
  std::unique_ptr<sf::RenderWindow> window;
  if (_settings->fullScreen())
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
      ERROR("Unsupported Video Mode, falling back");
      video_mode = sf::VideoMode::getDesktopMode(); // falling back to desktop mode
      if (!video_mode.isValid()) {
        std::exit(-1); // This time we quit  /// \todo browse all supported modes
      }
    }

    window = std::make_unique<sf::RenderWindow> (video_mode, "War Evolved");
  }

# ifndef DEBUG_PERFS
  window->setFramerateLimit(60);
# else
  window->setFramerateLimit(0);
#endif
  //_window->setIcon(64, 64, "icon");

  window->setKeyRepeatEnabled(false);

  graphics::GraphicsEngine::setWindow(std::move(window));
}
