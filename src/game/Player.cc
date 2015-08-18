#include <game/Player.hh>
#include <game/units/Soldier.hh>


Player::Player()
{
  static unsigned int static_id = 0;
  _id = static_id++;
}

// void Player::saveCursorPosition() {
//   _lastCursorPosition = CURSOR->coords();
// }

// void Player::endTurn()
// {
//   for (auto it: _units)
//     it->setPlayed(false);
// }


// void Player::removeUnit(std::shared_ptr<Unit> unit)
// {
//   auto u = std::find(_units.begin(), _units.end(), unit);
//   if (u == _units.end())
//   {
//     PRINTF("Unit not found");
//     return;
//   }

//   _units.erase(u);
//   _isDead = _isDead || _units.empty();
// }
