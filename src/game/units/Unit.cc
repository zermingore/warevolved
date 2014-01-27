#include <game/units/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <game/units/Team.hh>


Unit::Unit() :
  _imageId (0),
  _image (nullptr),
  _hp (0),
  _attackValue (1),
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
  _attackValue (1),
  _posX (0),
  _posY (0),
  _cellX (1),
  _cellY (1),
  _motionValue (4),
  _played (false),
  _playerId (0),
  _team (nullptr),
  _targetable (false)
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

// virtual method
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
  // we suppose the sprite is always larger than the cell
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

// virtual method
int Unit::receiveDamages(unsigned int damages)
{
  return _hp - damages;
}


void Unit::calcNbSteps()
{
}


// virtual method
void Unit::attack(Unit *target)
{
  calcNbSteps();

  unsigned int nb_steps = 2;
  for (unsigned int i = 0; i < nb_steps; ++i)
  {
    target->receiveDamages(_attackValue / nb_steps);
    if (!target)
      break;
    if (receiveDamages(target->getAttackValue() / nb_steps) < 1)
    {
      // TODO notify death
      break;
    }
  }
}
