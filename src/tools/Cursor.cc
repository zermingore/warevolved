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

// void changeOffset();


sf::Sprite Cursor::getSprite()
{
  // we're also adding offset (a semi cell)
  _sprite->setPosition((_x + 0.5) * g_cell_size, (_y + 0.5) * g_cell_size);

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
  _x = std::min(_x, _x - 1); // we're in unsigned so MIN
}

void Cursor::moveRight()
{
  _x = std::min(_x + 1, g_gridSizeX - 1);
}
