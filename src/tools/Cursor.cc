#include <tools/Cursor.hh>
#include <common/globals.hh>


Cursor::Cursor() :
  _x (0),
  _y (0)
{
  if (!_texture.loadFromFile("cursor.png"))
  {
	#ifdef DEBUG
	std::cerr << "Unable to LOAD the Texture (perhaps missing file)" << std::endl;
	std::exit(EXIT_FAILURE);
	#endif

	// TODO in release, load with a default sprite and report this in a log
  }

  _sprite = new sf::Sprite(_texture);
}

Cursor::~Cursor()
{
}

sf::Sprite Cursor::getSprite()
{
  return *_sprite;
}

sf::Sprite Cursor::getSprite(int offset_x, int offset_y)
{
  _sprite->setPosition(_x * g_cell_size + offset_x, _y * g_cell_size + offset_y);

  return *_sprite;
}


void Cursor::setX(unsigned int x)
{
  _x = x;
}

void Cursor::setY(unsigned int y)
{
  _y = y;
}


// Cursor Motion
void Cursor::moveUp()
{
  _y = std::min(_y - 1, _y);
}

void Cursor::moveDown()
{
  _y = std::min(_y + 1, g_gridSizeY - 1);
}

void Cursor::moveLeft()
{
  _x = std::min(_x, _x - 1);
}

void Cursor::moveRight()
{
  _x = std::min(_x + 1, g_gridSizeX - 1);
}
