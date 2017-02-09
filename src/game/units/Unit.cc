#include <game/units/Unit.hh>
#include <game/Cell.hh>


Unit::Unit()
  : _hp(0)
  , _attackValue(0)
  , _range(0, 0)
  , _motionValue(0)
  , _played(false)
  , _playerId(0)
  , _team(nullptr)
  , _targetable(false)
{
  _targets = std::make_shared<std::vector<std::shared_ptr<Cell>>> ();
}

Unit::Unit(std::string &name)
  : Unit::Unit()
{
  _name = name;
//  buildUnit(name);
}

int Unit::receiveDamages(const unsigned int damages)
{
  _hp -= damages;
  return _hp;
}

void Unit::setCoords(const Coords location)
{
  _coords = location;
  _attackCoords = _coords;
//  _played = true;
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


// virtual method
 /// \todo move into Map
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
  //      /// \todo notify death
  //     auto itself (CELLS[_coords.x][_coords.y]->unit());
  //     g_status->battle()->getPlayer(_playerId)->removeUnit(itself);
  //     CELLS[_coords.x][_coords.y]->removeUnit();
  //     return false;;
  //   }
  // }

  return true;
}
