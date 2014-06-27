#include <game/units/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <game/units/Team.hh>


Unit::Unit() :
  _imageId (0),
  _hp (0),
  _attackValue (0),
  _played (false),
  _playerId (0),
  _team (nullptr),
  _targetable (false)
{
  _targets = std::make_shared<std::vector<std::shared_ptr<Cell>>> ();
}

Unit::Unit(std::string &name) :
  _imageId (0),
  _name (name),
  _hp (0),
  _attackValue (0),
  _range (0, 0),
  _motionValue (4),
  _played (false),
  _playerId (0),
  _team (nullptr),
  _targetable (false)
{
  _targets = std::make_shared<std::vector<std::shared_ptr<Cell>>> ();
}

void Unit::pack(std::shared_ptr<Unit> unit) {
  _team->addMember(unit);
}

void Unit::setCoords(Coords location)
{
  _coords = location;
  _played = true;
}

void Unit::draw()
{
  Image &image = GETIMAGE(_name);
  image.sprite()->setColor(BATTLE->getPlayer(_playerId)->unitsColor());

  float x = image.sprite()->getTexture()->getSize().x;
  float y = image.sprite()->getTexture()->getSize().y;
  image.sprite()->setScale(CELL_WIDTH / x, CELL_HEIGHT / y);

# ifdef DEBUG
  // we suppose the sprite is always larger than the cell
  if (x < CELL_WIDTH || y < CELL_HEIGHT)
    Debug::logPrintf("Sprite scale failure");
# endif

  if (_targetable)
  {
    // Unit's image halo
    Image &highlight = GETIMAGE("highlight");
    highlight.sprite()->setColor(sf::Color(255, 0, 0));
    highlight.drawAtCell(_coords);
  }

  if (_played)
    image.sprite()->setColor(sf::Color(127, 127, 127, 191));

  image.drawAtCell(_coords);
}

// virtual method
void Unit::attack()
{
  auto target = (*_targets)[_targetIndex]->unit();
  unsigned int nb_steps = 2; // = calcNbSteps();
  for (unsigned int i = 0; i < nb_steps; ++i)
  {
    PRINTF("target:", target);

    if (target->receiveDamages(_attackValue / nb_steps) < 1)
    {
      PRINTF("target down");
      g_status->battle()->getPlayer(target->playerId())->removeUnit(target);
      CELLS[target->x()][target->y()]->removeUnit();
      break;
    }
    if (receiveDamages(target->attackValue() / nb_steps) < 1)
    {
      // TODO notify death
      break;
    }
  }
}
