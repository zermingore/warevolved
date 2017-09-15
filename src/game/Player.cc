#include <game/Player.hh>

#include <common/enums/states.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/units/Soldier.hh>
#include <interface/Interface.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Cursor.hh>
#include <interface/Panel.hh>
#include <interface/menus/InGameMenu.hh>
#include <context/State.hh>
#include <context/StateMenu.hh>


Player::Player(const graphics::Color c)
{
  static size_t static_id = 0;
  _id = static_id++;

  _color = c;

  // Interface and elements
  _interface = std::make_shared<interface::Interface> (c);

  _cursor = std::make_shared<interface::Cursor> ();
  _cursor->setColor(c);
  _interface->addElement(_cursor);

  _panel = std::make_shared<interface::Panel> (game::Status::battle()->map(),
                                               _cursor);
  _interface->addElement(_panel);
}


// Interface elements
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

void Player::togglePanel() {
  _panel->toggleStatus();
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
