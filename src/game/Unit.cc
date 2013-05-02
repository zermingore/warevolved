#include <game/Unit.hh>

Unit::Unit() {
}

Unit::Unit(Cell* cell) {
  _cell = cell;
}

Unit::~Unit() {
}


unsigned int Unit::getX() {
  return _x;
}


unsigned int Unit::getY() {
  return _y;
}


unsigned int Unit::getTextureId() {
  return _textureId;
}


void Unit::setTextureId(unsigned int texture_id) {
  _textureId = texture_id;
}
