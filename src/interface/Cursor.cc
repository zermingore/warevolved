#include <interface/Cursor.hh>



Cursor::Cursor()
  : _nbColumns (0)
  , _nbLines (0)
  , _image ("cursor")
  , _color (Color(255, 0, 0, 255))
{
  // _sprite = _image.sprite();
  // _center.x = _image.getTexture()->getSize().x / 2;
  // _center.y = _image.getTexture()->getSize().y / 2;
}


Cursor::Cursor(size_t nb_columns, size_t nb_lines)
  : _nbColumns (nb_columns)
  , _nbLines (nb_lines)
  , _image ("cursor")
  , _color (Color(255, 0, 0, 255))
{
}

// std::shared_ptr<sf::Sprite> Cursor::sprite(int offset_x, int offset_y)
// {
//   // static unsigned int angle = 0;
//   // _sprite->setOrigin(_center);
//   // _sprite->setRotation(angle++);

//   // // scale is function of rotation
//   //  /// \todo setup a timer to dissociate rotation and scale
//   // static float scale_factor = 1;
//   // angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
//   // _sprite->setScale(scale_factor, scale_factor);

//   // // finally, replace the cursor at it's true position before returning it
//   // _sprite->setPosition(_coords.x * CELL_WIDTH + offset_x + _center.x,
//   //                      _coords.y * CELL_HEIGHT + offset_y + _center.y);

//   // return _sprite;
// }

void Cursor::setLimits(size_t nbColumns, size_t nbLines)
{
  _nbColumns = nbColumns;
  _nbLines = nbLines;
}

// _____________________________ Cursor Motion _____________________________ //
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
