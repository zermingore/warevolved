#include <interface/Cursor.hh>
#include <common/globals.hh>


Cursor::Cursor() :
  _nbColumns (0),
  _nbLines (0)
{
  _image = GETIMAGE("cursor");
  _sprite = _image->getSprite();
  _middle.x = _image->getTexture()->getSize().x / 2;
  _middle.y = _image->getTexture()->getSize().y / 2;
}

Cursor::Cursor(unsigned int nbColumns, unsigned int nbLines) :
  _nbColumns (nbColumns),
  _nbLines (nbLines)
{
  _image = GETIMAGE("cursor");
  _sprite = _image->getSprite();
  _middle.x = _image->getTexture()->getSize().x / 2;
  _middle.y = _image->getTexture()->getSize().y / 2;
}

Cursor::~Cursor()
{
# ifdef DEBUG
  std::cout << "Cursor Dtor" << std::endl;
# endif
}

/// \deprecated
unsigned int Cursor::getX() {
  return _coords.x;
}

/// \deprecated
unsigned int Cursor::getY() {
  return _coords.y;
}

Coords Cursor::getCoords() {
  return _coords;
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
  _sprite->setPosition(_coords.x * CELL_WIDTH + offset_x + _middle.x,
                       _coords.y * CELL_HEIGHT + offset_y + _middle.y);

  return *_sprite;
}


void Cursor::setX(unsigned int x) {
  _coords.x = x;
}

void Cursor::setY(unsigned int y) {
  _coords.y = y;
}

void Cursor::setCoords(Coords coords) {
  _coords = coords;
}

void Cursor::setLimits(unsigned int nbColumns, unsigned int nbLines)
{
  _nbColumns = nbColumns;
  _nbLines = nbLines;
}


// Cursor Motion
bool Cursor::moveUp()
{
  unsigned int old = _coords.y;
  _coords.y = std::min(_coords.y - 1, _coords.y);

  return (old != _coords.y);
}

bool Cursor::moveDown()
{
  unsigned int old = _coords.y;
  _coords.y = std::min(_coords.y + 1, _nbLines - 1);

  return (old != _coords.y);
}

bool Cursor::moveLeft()
{
  unsigned int old = _coords.x;
  _coords.x = std::min(_coords.x, _coords.x - 1);

  return (old != _coords.x);
}

bool Cursor::moveRight()
{
  unsigned int old = _coords.x;

  _coords.x = std::min(_coords.x + 1, _nbColumns - 1);
  return (old != _coords.x);
}

void Cursor::draw() {
  _image->draw();
}
