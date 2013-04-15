#include <tools/Cursor.hh>
#include <common/globals.hh>


Cursor::Cursor()
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
  _sprite->setPosition(g_cell_size / 2, g_cell_size / 2);

  return *_sprite;
}


void Cursor::setX(unsigned int x)
{
  _x = x;
}

void  Cursor::setY(unsigned int y)
{
  _y = y;
}
