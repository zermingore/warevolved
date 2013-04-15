#include <core/Context.hh>
#include <common/System.hh>
#include <common/Settings.hh>
#include <common/globals.hh>

unsigned int g_cell_size = 64; // > arbitrary value, in px <
unsigned int g_grid_thickness = 5;


Context::Context()
{
  _settings = new Settings(0, 0, 0); // depth, stencil, alias
  _system = new System(2, 0);
}

Context::Context(bool fullscreen)
{
  if (fullscreen)
	_settings = new Settings(24, 8, 4);
  else
	_settings = new Settings(0, 0, 0); // more or less debug

  _system = new System(2, 0);
}

Context::~Context()
{
}


sf::RenderWindow* Context::init()
{
#ifdef DEBUG
  std::cout << _settings->getDepth() << " "
			<< _settings->getStencil() << " "
			<< _settings->getAntialiasing() << " "
			<< _system->getSfmlMajor() << " "
			<< _system->getSfmlMinor()
			<< std::endl;
#endif

  sf::ContextSettings contextSettings(_settings->getDepth(),
  									  _settings->getStencil(),
  									  _settings->getAntialiasing(),
  									  _system->getSfmlMajor(),
  									  _system->getSfmlMinor());

  // getting right resolution, from desktop
  if (_settings->getFullscreen())
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

  // sf::Window w(sf::VideoMode(video_mode), "WE", sf::Style::Fullscreen);
  // w.Create(sf::VideoMode(800, 600, 32), "SFML Window", sf::Style::Fullscreen, 4);

  return _window;
}
