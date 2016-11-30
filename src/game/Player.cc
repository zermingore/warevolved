#include <game/Player.hh>
#include <game/units/Soldier.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <common/Status.hh>
#include <common/enums/states.hh>
#include <context/State.hh>
#include <context/StateMenu.hh>
#include <game/applications/Battle.hh>


Player::Player(Color c)
{
  static size_t static_id = 0;
  _id = static_id++;

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
  _menu = std::make_shared<interface::InGameMenu> ();
  _menu->setCoords(_cursor->coords());
  _menu->build();
  _interface->addElement(_menu);
  _interface->setCurrentMenu(_menu);

  Status::pushState(e_state::MENU);
}


void Player::cancel()
{
  _interface->removeElement(_menu);
}



// _____________________________  Units motion _____________________________ //

// tmp
void Player::moveUnitUp()
{
  moveCursorUp();
}

void Player::moveUnitDown()
{
  moveCursorDown();
}

void Player::moveUnitLeft()
{
  moveCursorLeft();
}

void Player::moveUnitRight()
{
  moveCursorRight();
}

void Player::validateMoveUnit()
{
//  Status::battle()->map()->moveUnit();
}


bool Player::updateSelectedUnit()
{
  // update the Map selected Unit
  auto coords(Status::player()->cursor()->coords());
  if (Status::battle()->map()->selectUnit(coords) == false) {
    Debug::error("Unable to select a unit");
    return false;
  }

  return true;
}
