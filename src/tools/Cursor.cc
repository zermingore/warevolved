#include <tools/Cursor.hh>
#include <common/globals.hh>


Cursor::Cursor() :
  _x (0),
  _y (0)
{
  if (!_texture.loadFromFile("cursor.png"))
  {
	#ifdef DEBUG
	std::exit(EXIT_FAILURE);
	#endif

	// TODO in release, load with a default sprite and report this in a log
  }

  _sprite = new sf::Sprite(_texture);
  _timer.restart();

  _middle.x = _texture.getSize().x / 2;
  _middle.y = _texture.getSize().y / 2;
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
  static int angle = 0;
  // setRotation(): auto-frame limit (<> rotate())
  _sprite->setOrigin(_middle);
  _sprite->setRotation(angle++); // Origin: top left => draw a nice target :)

  // scale is function of rotation
  // TODO setup a timer to dissociate rotation and scale
  static float scale_factor = 1;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  _sprite->setScale(scale_factor, scale_factor);

  // finally, replace the cursor at it's true position before returning it
  _sprite->setPosition(_x * g_cell_size + offset_x + _middle.x,
					   _y * g_cell_size + offset_y + _middle.y);

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
