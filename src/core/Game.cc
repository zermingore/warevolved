#include <core/Game.hh>
#include <core/GraphicEngine.hh>
#include <tools/Cursor.hh>


Game::Game()
{
  std::cerr << "Must specify a window" << std::endl;
}

Game::Game(sf::RenderWindow* window)
{
  _window = window;
}

Game::~Game()
{
}


void Game::drawLine(sf::Vector2f a, sf::Vector2f b)
{
  sf::Vertex line[2] = {a, b};
  _window->draw(line, 2, sf::Lines);
}

int Game::run()
{
  GraphicEngine* graphics = new GraphicEngine(_window, new Cursor());

  // Start the game loop
  while (_window->isOpen())
  {
	this->manageEvents();

	graphics->drawGrid(5, 5);

	// Update the window
	_window->display();
  }

  return 0;
}


void Game::manageEvents()
{
  sf::Event event;

  while (_window->pollEvent(event))
  {
	// Close window : exit
	if (event.type == sf::Event::Closed)
	{
	  _window->close();
	}
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
  {
	_window->close();
  }
}
