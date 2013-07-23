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
  static unsigned int angle = 0;
  _sprite->setOrigin(_middle);
  _sprite->setRotation(angle++);

  // scale is function of rotation
  // TODO setup a timer to dissociate rotation and scale
  static float scale_factor = 1;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  _sprite->setScale(scale_factor, scale_factor);

  // finally, replace the cursor at it's true position before returning it
  _sprite->setPosition(_x * CELL_WIDTH + offset_x + _middle.x,
                       _y * CELL_HEIGHT + offset_y + _middle.y);

  return *_sprite;
}


void Cursor::setX(unsigned int x) {
  _x = x;
}

void Cursor::setY(unsigned int y) {
  _y = y;
}


// Cursor Motion
bool Cursor::moveUp()
{
  unsigned int old = _y;
  _y = std::min(_y - 1, _y);

  return (old != _y);
}

bool Cursor::moveDown()
{
  unsigned int old = _y;
  _y = std::min(_y + 1, _nbLines - 1);

  return (old != _y);
}

bool Cursor::moveLeft()
{
  unsigned int old = _x;
  _x = std::min(_x, _x - 1);

  return (old != _x);
}

bool Cursor::moveRight()
{
  unsigned int old = _x;

  _x = std::min(_x + 1, _nbColumns - 1);
  return (old != _x);
}

void Cursor::draw() {
  _image->draw();
}
