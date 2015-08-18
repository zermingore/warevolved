#include <game/units/Unit.hh>
#include <common/include.hh>
#include <game/units/Team.hh>
#include <resources/ResourcesManager.hh>
#include <resources/Image.hh>
#include <game/Cell.hh>


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
  --_targetIndex %= _targets->size();
  return (*_targets)[_targetIndex];
}

std::shared_ptr<Cell> Unit::nextTarget()
{
  ++_targetIndex %= _targets->size();
  return (*_targets)[_targetIndex];
}

void Unit::draw()
{
//   graphics::Image &image = resources::ResourcesManager::getImage(_name);
//   image.sprite()->setColor(BATTLE->getPlayer(_playerId)->unitsColor());

//   float x = image.sprite()->getTexture()->getSize().x;
//   float y = image.sprite()->getTexture()->getSize().y;
//   image.sprite()->setScale(CELL_WIDTH / x, CELL_HEIGHT / y);

// # ifdef DEBUG
//   // we suppose the sprite is always larger than the cell
//   if (x < CELL_WIDTH || y < CELL_HEIGHT)
//     Debug::logPrintf("Sprite scale failure");
// # endif

//   if (_targetable)
//   {
//     // Unit's image halo
//     Image &highlight = GETIMAGE("highlight");
//     highlight.sprite()->setColor(sf::Color(255, 0, 0));
//     highlight.drawAtCell(_coords);
//   }

//   if (_played)
//     image.sprite()->setColor(sf::Color(127, 127, 127, 191));

//   image.drawAtCell(_coords);
}


// virtual method
// TODO move into Map
bool Unit::attack(// std::shared_ptr<Unit> target
  )
{
  // size_t nb_steps = 2; // = calcNbSteps();
  // for (auto i = 0; i < nb_steps; ++i)
  // {
  //   if (target->receiveDamages(_attackValue / nb_steps) < 1)
  //   {
  //     g_status->battle()->getPlayer(target->playerId())->removeUnit(target);
  //     CELLS[target->x()][target->y()]->removeUnit();
  //     return true;
  //   }
  //   if (receiveDamages(target->attackValue() / nb_steps) < 1)
  //   {
  //     // TODO notify death
  //     auto itself (CELLS[_coords.x][_coords.y]->unit());
  //     g_status->battle()->getPlayer(_playerId)->removeUnit(itself);
  //     CELLS[_coords.x][_coords.y]->removeUnit();
  //     return false;;
  //   }
  // }

  return true;
}
