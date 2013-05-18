#include <core/Context.hh>
#include <common/System.hh>
#include <common/Settings.hh>
#include <common/globals.hh>

Settings *g_settings = new Settings();


Context::Context()
{
  g_settings = new Settings(0, 0, 0); // depth, stencil, alias
  _system = new System(2, 0);
}

Context::Context(bool fullscreen)
{
  if (fullscreen)
  {
	g_settings = new Settings(24, 8, 4);
	g_settings->setFullScreen(true);
  }
  else
	g_settings = new Settings(0, 0, 0); // vanilla (debug) mode

  _system = new System(2, 0);
}

Context::~Context()
{
  delete g_settings;
  delete _system;
}


sf::RenderWindow* Context::init()
{
#ifdef DEBUG
  if (_system->getSfmlMajor() < 2)
	std::cerr << "SFML version not officially supported" << std::endl;
#endif

  sf::ContextSettings contextSettings(g_settings->getDepth(),
  									  g_settings->getStencil(),
  									  g_settings->getAntiAliasing(),
  									  _system->getSfmlMajor(),
  									  _system->getSfmlMinor());

  // getting right resolution, from desktop
  if (g_settings->getFullScreen())
  {
	_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),
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

	_window = new sf::RenderWindow(video_mode, "War Evolved");
  }

  _window->setFramerateLimit(60);
  //_window->setIcon(64, 64, "icon");

  // Deducing some Status
  g_status->setCellWidth(64); // TODO change dynamically (in px)
  g_status->setCellHeight(64); // TODO change dynamically (in px)
  g_status->setGridThickness(5); // TODO change dynamically (in px)

  return _window;
}
