#include <interface/Cursor.hh>
#include <common/globals.hh>


Cursor::Cursor() :
  _nbColumns (0),
  _nbLines (0),
  _x (0),
  _y (0)
{
  _image = GETIMAGE("cursor");
  _sprite = _image->getSprite();
  _texture = _image->getTexture();

  _middle.x = _texture->getSize().x / 2;
  _middle.y = _texture->getSize().y / 2;
}

Cursor::Cursor(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines),
  _x (0),
  _y (0)
{
  _image = GETIMAGE("cursor");
  _sprite = _image->getSprite();
  _texture = _image->getTexture();

  _middle.x = _texture->getSize().x / 2;
  _middle.y = _texture->getSize().y / 2;
}

Cursor::~Cursor() {
# ifdef DEBUG
  std::cout << "Cursor Dtor" << std::endl;
# endif
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
  _sprite->setPosition(_x * g_status->getCellWidth() + offset_x + _middle.x,
					   _y * g_status->getCellHeight() + offset_y + _middle.y);

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

void Cursor::draw() {
  _image->draw();
}
