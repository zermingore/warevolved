/**
 * \file
 * \brief Cursor class definition.
 *
 * User Interface's Cursor
 */

#include <interface/Cursor.hh>


namespace interface {

Cursor::Cursor()
  : InterfaceElement("cursor")
{
}


void Cursor::setLimits(size_t nb_columns, size_t nb_lines)
{
  _nbColumns = nb_columns;
  _nbLines = nb_lines;
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

  setPosition(_coords);

  return (old != _coords.x);
}


void Cursor::update()
{
  _rotation += 1;
  _position.x = _coords.x * 64;
  _position.y = _coords.y * 64;
  std::cout << "cursor update "
            << _position.x << ', ' << _position.y << std::endl;
}



} // namespace interface
