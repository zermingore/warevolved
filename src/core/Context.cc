#include <core/Context.hh>
#include <common/System.hh>
#include <common/Settings.hh>
#include <common/globals.hh>

unsigned int g_cell_size = 64; // TODO change dynamically (in px)
unsigned int g_grid_thickness = 5;
Settings* g_player_settings;


Context::Context()
{
  _settings = new Settings(0, 0, 0); // depth, stencil, alias
  _system = new System(2, 0);
}

Context::Context(bool fullscreen)
{
  if (fullscreen)
  {
	_settings = new Settings(24, 8, 4);
	_settings->setFullScreen(true);
  }
  else
	_settings = new Settings(0, 0, 0); // vanilla (debug) mode

  _system = new System(2, 0);
}

Context::~Context()
{
  delete _settings;
  delete _system;
  delete _window;
}


sf::RenderWindow* Context::init()
{
#ifdef DEBUG
  if (_system->getSfmlMajor() < 2)
	std::cerr << "SFML version not officially supported" << std::endl;
#endif

  sf::ContextSettings contextSettings(_settings->getDepth(),
  									  _settings->getStencil(),
  									  _settings->getAntiAliasing(),
  									  _system->getSfmlMajor(),
  									  _system->getSfmlMinor());

  // getting right resolution, from desktop
  if (_settings->getFullScreen())
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

  g_player_settings = _settings;

  return _window;
}
