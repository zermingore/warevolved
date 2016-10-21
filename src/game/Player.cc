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

  _interface->addElement(_cursor);
}



void Player::moveCursorUp() {
  _cursor->moveUp();
}


void Player::moveCursorDown() {
  _cursor->moveDown();
}

void Player::moveCursorLeft() {
  _cursor->moveLeft();
}


void Player::moveCursorRight() {
  _cursor->moveRight();
}
