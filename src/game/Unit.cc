#include <game/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>

Unit::Unit() :
  _imageId (0),
  _name (""),
  _image (nullptr),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1),
  _played (false),
  _playerId (0)
{
}

Unit::Unit(std::string name) :
  _imageId (0),
  _name (name),
  _image (nullptr),
  _hp (0),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1),
  _motionValue (4),
  _played (false),
  _playerId (0)
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

void Unit::setPlayerId(unsigned int player_id) {
  _playerId = player_id;
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

void Unit::setLocation(Coords location)
{
  _location = location;
  _played = true;
}

unsigned int Unit::getPlayerId() {
  return _playerId;
}


void Unit::draw()
{
  _image = GETIMAGE(_name);
  _image->getSprite()->setColor(g_status->getPlayers()[_playerId]->getUnitsColor());
  _image->drawAtCell(_cellX, _cellY);
}
