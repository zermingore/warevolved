/**
 * \file
 * \brief Cursor class definition.
 *
 * User Interface's Cursor
 */

#include <interface/Cursor.hh>
#include <graphics/GraphicsEngine.hh>


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
  auto old(_coords.y);
  _coords.y = std::min(_coords.y - 1, _coords.y);

  return (old != _coords.y);
}

bool Cursor::moveDown()
{
  auto old(_coords.y);
  _coords.y = std::min(_coords.y + 1, _nbLines - 1);

  return (old != _coords.y);
}

bool Cursor::moveLeft()
{
  auto old(_coords.x);
  _coords.x = std::min(_coords.x, _coords.x - 1);

  return (old != _coords.x);
}

bool Cursor::moveRight()
{
  auto old(_coords.x);
  _coords.x = std::min(_coords.x + 1, _nbColumns - 1);

  return (old != _coords.x);
}


void Cursor::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  _position.x = _coords.x * width + properties->gridOffsetX() + width / 2;
  _position.y = _coords.y * height + properties->gridOffsetY() + height / 2;
  _image.sprite()->setPosition(_position.x, _position.y);

  static float scale_factor = 1;
  static unsigned int angle = 0;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  _image.setScale(scale_factor, scale_factor);
  ++angle;


  // The origin of the sprite is the middle of the cell
  _image.sprite()->setOrigin(width / 2, height / 2);
  _image.sprite()->setRotation(angle);
  _image.setScale(scale_factor, scale_factor);

  _image.sprite()->setColor(_color);
}


void Cursor::draw()
{
  graphics::GraphicsEngine::draw(_image.sprite());
}


} // namespace interface
