#include <game/Player.hh>
#include <game/units/Soldier.hh>


Player::Player(Color c)
{
  static size_t static_id = 0;
  _id = static_id++;
  _interface = std::make_shared<interface::Interface> (c);
}
