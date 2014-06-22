#include <game/Player.hh>
#include <common/globals.hh>
#include <game/units/Soldier.hh>


Player::Player() :
  _isDead (false),
  _faction (E_FACTION_T)
{
  static unsigned int static_id = 0;
  _index = static_id++;
}

void Player::saveCursorPosition() {
  _lastCursorPosition = CURSOR->coords();
}

void Player::endTurn()
{
  for (auto it: _units)
    it->setPlayed(false);
}

std::shared_ptr<Unit> Player::newUnit(e_unit unit,
                                      unsigned int line, unsigned int column)
{
  std::shared_ptr<Unit> new_unit;
  switch (unit)
  {
    case E_UNIT_SOLDIERS:
      new_unit = std::make_shared<Soldier> ();
      break;

    default:
      DEBUG_PRINT("Unable to match this unit type");
      return nullptr;
  }

  new_unit->setCellCoordinates(line, column);
  new_unit->setPlayerId(_index);
  _units.push_back(new_unit);

  return new_unit;
}


void Player::removeUnit(std::shared_ptr<Unit> unit)
{
  auto u = std::find(_units.begin(), _units.end(), unit);
  if (u == _units.end())
  {
    PRINTF("Unit not found");
    return;
  }

  _units.erase(u);
  _isDead = _isDead || _units.empty();
}
