#include <game/units/Unit.hh>
#include <common/include.hh>
#include <common/globals.hh>
#include <game/units/Team.hh>
#include <common/Text.hh>


Unit::Unit() :
  _imageId (0),
  _rank (E_RANK_PRIVATE),
  _played (false),
  _team (nullptr),
  _targetable (false)
{
  _targets = std::make_shared<std::vector<std::shared_ptr<Cell>>> ();
}

std::string Unit::getRank() {
  return Text::name(_rank);
}

int Unit::receiveDamages(unsigned int damages)
{
  _hp -= damages;
  return _hp;
}

void Unit::pack(std::shared_ptr<Unit> unit) {
  _team->addMember(unit);
}

void Unit::setCoords(Coords location)
{
  _coords = location;
  _attackCoords = _coords;
  _played = true;
}

std::shared_ptr<Cell> Unit::previousTarget()
{
  if (_targetIndex == 0)
  {
    _targetIndex = _targets->size() - 1;
    return (*_targets)[_targetIndex];
  }

  _targetIndex = (_targetIndex - 1) % (_targets->size() - 1);
  return (*_targets)[_targetIndex];
}

std::shared_ptr<Cell> Unit::nextTarget()
{
  ++_targetIndex %= _targets->size();
  return (*_targets)[_targetIndex];
}

void Unit::draw()
{
  Image &image = GETIMAGE(_class);
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
bool Unit::attack()
{
  auto target = (*_targets)[_targetIndex]->unit();
  unsigned int nb_steps = 2; // = calcNbSteps();
  for (unsigned int i = 0; i < nb_steps; ++i)
  {
    if (target->receiveDamages(_attackValue / nb_steps) < 1)
    {
      g_status->battle()->getPlayer(target->playerId())->removeUnit(target);
      CELLS[target->x()][target->y()]->removeUnit();
      return true;
    }
    if (receiveDamages(target->attackValue() / nb_steps) < 1)
    {
      // TODO notify death
      auto itself (CELLS[_coords.x][_coords.y]->unit());
      g_status->battle()->getPlayer(_playerId)->removeUnit(itself);
      CELLS[_coords.x][_coords.y]->removeUnit();
      return false;;
    }
  }

  return true;
}
