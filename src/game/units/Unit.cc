#include <game/units/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <game/units/Team.hh>


Unit::Unit() :
  _imageId (0),
  //_name (""),
  _image (nullptr),
  _hp (0),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1),
  _played (false),
  _playerId (0),
  _team (nullptr),
  _targetable (false)
{
  DEBUG_PRINT("UNIT CTOR");
  _highlight = GETIMAGE("highlight");
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
  _highlight = GETIMAGE("highlight");
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

bool Unit::getPlayed() {
  return _played;
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

std::string Unit::getName() {
  return _name;
}

void Unit::setLocation(Coords location)
{
  _location = location;
  _played = true;
}

unsigned int Unit::getPlayerId() {
  return _playerId;
}

void Unit::setPlayed(bool played) {
  _played = played;
}


void Unit::draw()
{
  _image = GETIMAGE(_name);
  _image->getSprite()->setColor(g_status->getPlayers()[_playerId]->getUnitsColor());

  float x = _image->getSprite()->getTexture()->getSize().x;
  float y = _image->getSprite()->getTexture()->getSize().y;
  _image->getSprite()->setScale(CELL_WIDTH / x, CELL_HEIGHT / y);

  # ifdef DEBUG
  if (x < CELL_WIDTH || y < CELL_HEIGHT)
    std::cerr << "Sprite scale failure" << std::endl;
  # endif

  if (_targetable)
  {
    _highlight->getSprite()->setColor(sf::Color(255, 0, 0));
    _highlight->drawAtCell(_cellX, _cellY);
  }

  if (_played)
    _image->getSprite()->setColor(sf::Color(127, 127, 127, 191));

  _image->drawAtCell(_cellX, _cellY);
}


void Unit::pack(Unit *unit) {
  _team->addMember(unit);
}
