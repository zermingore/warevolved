#include <game/Cursor.hh>
#include <common/globals.hh>
#include <common/Settings.hh>


Cursor::Cursor() {
}

Cursor::Cursor(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines),
  _x (0),
  _y (0)
{
  _texture.loadFromFile(g_player_settings->getCursorFileName());

  _sprite = new sf::Sprite(_texture);
  _middle.x = _texture.getSize().x / 2;
  _middle.y = _texture.getSize().y / 2;
}

Cursor::~Cursor() {
  delete _sprite;
}


unsigned int Cursor::getX() {
  return _x;
}

unsigned int Cursor::getY() {
  return _y;
}

sf::Sprite Cursor::getSprite() {
  return *_sprite;
}

sf::Sprite Cursor::getSprite(int offset_x, int offset_y)
{
  static int angle = 0;
  _sprite->setOrigin(_middle);
  _sprite->setRotation(angle++);

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


void Cursor::setX(unsigned int x) {
  _x = x;
}

void Cursor::setY(unsigned int y) {
  _y = y;
}


// Cursor Motion
void Cursor::moveUp() {
  _y = std::min(_y - 1, _y);
}

void Cursor::moveDown() {
  _y = std::min(_y + 1, _nbLines - 1);
}

void Cursor::moveLeft() {
  _x = std::min(_x, _x - 1);
}

void Cursor::moveRight() {
  _x = std::min(_x + 1, _nbColumns - 1);
}
