#include <game/Player.hh>
#include <game/units/Soldier.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <common/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>
#include <context/StateMenu.hh>
#include <game/Battle.hh>


Player::Player(const graphics::Color c)
{
  static size_t static_id = 0;
  _id = static_id++;

  _color = c;

  // Cursor
  _cursor = std::make_shared<interface::Cursor> ();
  _cursor->setColor(c);

  // Interface
  _interface = std::make_shared<interface::Interface> (c);
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


void Player::select()
{
  /// \todo check selectable before push

  if (game::Status::battle()->map()->unit(_cursor->coords()))
  {
    game::Status::pushState(e_state::SELECTION_UNIT);
  }
  else
  {
    game::Status::pushState(e_state::MAP_MENU);
  }
  game::Status::currentState()->resume();
}


void Player::updateSelectedUnit()
{
  game::Status::battle()->map()->selectUnit(_cursor->coords());
}
