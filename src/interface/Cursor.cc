/**
 * \file
 * \brief Cursor class definition.
 *
 * User Interface's Cursor
 */

#include <interface/Cursor.hh>

#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>


namespace interface {

Cursor::Cursor()
  : InterfaceElement("cursor")
{
}


void Cursor::setLimits(const size_t nb_columns, const size_t nb_lines)
{
  _nbColumns = nb_columns;
  _nbLines = nb_lines;
}


// _____________________________ Cursor Motion _____________________________ //
bool Cursor::moveUp()
{
  auto old(_coords.l);
  _coords.l = std::min(_coords.l - 1, _coords.l);

  return (old != _coords.l);
}

bool Cursor::moveDown()
{
  auto old(_coords.l);
  _coords.l = std::min(_coords.l + 1, _nbLines - 1);

  return (old != _coords.l);
}

bool Cursor::moveLeft()
{
  auto old(_coords.c);
  _coords.c = std::min(_coords.c, _coords.c - 1);

  return (old != _coords.c);
}

bool Cursor::moveRight()
{
  auto old(_coords.c);
  _coords.c = std::min(_coords.c + 1, _nbColumns - 1);

  return (old != _coords.c);
}


void Cursor::update()
{
  using namespace graphics;
  using p = MapGraphicsProperties;

  auto w(p::cellWidth());
  auto h(p::cellHeight());

  _position = {
    static_cast<component> (_coords.c) * w + p::gridOffsetX() + w / 2,
    static_cast<component> (_coords.l) * h + p::gridOffsetY() + h / 2};
  _sprite->setPosition(_position.x, _position.y);

  static float scale_factor = 1;
  static uint16_t angle = 0;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  if (angle % 360 == 0)
  {
    angle = 0;
    scale_factor = 1;
  }
  _sprite->setScale(scale_factor, scale_factor);
  ++angle;


  // The origin of the sprite is the middle of the cell
  _sprite->setOrigin(w / 2.f, h / 2.f);
  _sprite->setRotation(static_cast<float> (angle));
  _sprite->setScale(scale_factor, scale_factor);

  _sprite->setColor(_color);
}


void Cursor::draw()
{
  _sprite->draw();
}


} // namespace interface
