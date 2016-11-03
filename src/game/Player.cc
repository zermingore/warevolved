#include <game/Player.hh>
#include <game/units/Soldier.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <common/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>


Player::Player(Color c)
{
  static size_t static_id = 0;
  _id = static_id++;

  _interface = std::make_shared<interface::Interface> (c);
  _cursor = std::make_shared<interface::Cursor> ();
  _menu = std::make_shared<interface::InGameMenu> ();
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


void Player::select() {
  Debug::printf("select");
  _menu->setCoords(_cursor->coords());
  _interface->addElement(_menu);
  Status::pushState(e_state::MENU);
}


void Player::cancel() {
}
