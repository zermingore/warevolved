/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \namespace graphics
 * \brief Context class definition
 */

#include <graphics/Context.hh>

#include <config/Settings.hh>
#include <debug/Debug.hh>
#include <graphics/GraphicsEngine.hh>

#include <X11/Xlib.h> // Must be included after SMFL includes


namespace graphics {


Context::Context(const bool fullscreen)
{
  // Initialize the Xlib support for concurrent threads.
  XInitThreads();

  Settings::setFullScreen(fullscreen);
  init();
}


void Context::init()
{
  sf::ContextSettings contextSettings(Settings::depth(),
                                      Settings::stencil(),
                                      Settings::antiAliasing(),
                                      Settings::sfmlMajor(),
                                      Settings::sfmlMinor());

  // getting right resolution, from desktop
  std::unique_ptr<sf::RenderWindow> window;
  if (Settings::fullScreen())
  {
    window = std::make_unique<sf::RenderWindow>
      (sf::VideoMode::getDesktopMode(),
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
      video_mode = sf::VideoMode::getDesktopMode(); // falling back mode
      if (!video_mode.isValid()) {
        std::exit(-1); /// \todo try all supported modes
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


} // namespace graphics
