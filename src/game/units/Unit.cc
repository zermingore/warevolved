#include <game/units/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <game/units/Team.hh>


Unit::Unit() :
  _imageId (0),
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
}

Unit::Unit(std::string name) :
  _imageId (0),
  _name (name),
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
}

void Unit::pack(Unit *unit)
{
  _team->addMember(unit);
}

void Unit::setCellCoordinates(unsigned int cell_x, unsigned int cell_y)
{
  _cellX = cell_x;
  _cellY = cell_y;
}

void Unit::setLocation(Coords location)
{
  _location = location;
  _played = true;
}

void Unit::draw()
{
  Image &image = GETIMAGE(_name);
  image.sprite()->setColor(g_status->players()[_playerId]->unitsColor());

  float x = image.sprite()->getTexture()->getSize().x;
  float y = image.sprite()->getTexture()->getSize().y;
  image.sprite()->setScale(CELL_WIDTH / x, CELL_HEIGHT / y);

  # ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (x < CELL_WIDTH || y < CELL_HEIGHT)
    std::cerr << "Sprite scale failure" << std::endl;
  # endif

  if (_targetable)
  {
    // Unit's image halo
    Image &highlight = GETIMAGE("highlight");
    highlight.sprite()->setColor(sf::Color(255, 0, 0));
    highlight.drawAtCell(_cellX, _cellY);
  }

  if (_played)
    image.sprite()->setColor(sf::Color(127, 127, 127, 191));

  image.drawAtCell(_cellX, _cellY);
}

// virtual method
void Unit::attack(Unit *target)
{
  unsigned int nb_steps = 2; // = calcNbSteps();
  for (unsigned int i = 0; i < nb_steps; ++i)
  {
    target->receiveDamages(_attackValue / nb_steps);
    if (!target)
      break;
    if (receiveDamages(target->attackValue() / nb_steps) < 1)
    {
      // TODO notify death
      break;
    }
  }
}
