#include <game/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>

Unit::Unit() :
  _imageId (0),
  _name (""),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1)
{
}

// Unit::Unit(Cell* cell)
// {
//   _cell = cell;
//   _name = "soldiers";
// }

Unit::Unit(std::string name) :
  _imageId (0),
  _name (name),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1),
  _motionValue (4)
{
}

Unit::~Unit() {
}


unsigned int Unit::getPosX() {
  return _posX;
}

unsigned int Unit::getPosY() {
  return _posY;
}

unsigned int Unit::getCellX() {
  return _cellX;
}

unsigned int Unit::getCellY() {
  return _cellY;
}

unsigned int Unit::getMotionValue() {
  return _motionValue;
}

void Unit::setCellCoordinates(unsigned int cell_x, unsigned int cell_y)
{
  _cellX = cell_x;
  _cellY = cell_y;
}

unsigned int Unit::getTextureId() {
  return _textureId;
}

void Unit::setTextureId(unsigned int texture_id) {
  _textureId = texture_id;
}

Coords Unit::getLocation() {
  return _location;
}

void Unit::setLocation(Coords location) {
  _location = location;
}


void Unit::draw()
{
  _image = GETIMAGE(_name);
  _image->drawAtCell(_cellX, _cellY);
}
