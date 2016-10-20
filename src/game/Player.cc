#include <game/Player.hh>
#include <game/units/Soldier.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Cursor.hh>


Player::Player(Color c)
{
  static size_t static_id = 0;
  _id = static_id++;
  _interface = std::make_shared<interface::Interface> (c);

  _cursor = std::make_shared<interface::Cursor> ();

  // interface::InterfaceElement elt("cursor");
  // elt.setPosition(_cursor->coords());
  // elt.setRotation(45.);
  // elt.setScale(.1);

  _interface->addElement(_cursor);
}


void Player::moveCursorRight() {
  std::cout << "->" << std::endl;
  _cursor->moveRight();
}
