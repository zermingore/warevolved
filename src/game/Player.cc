/**
 * \file
 * \date August 1, 2013
 * \author Zermingore
 * \brief Player class definition
 */

#include <game/Player.hh>

#include <context/State.hh>
#include <context/StateMenu.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/units/Soldier.hh>
#include <interface/Cursor.hh>
#include <interface/Interface.hh>
#include <interface/InterfaceElement.hh>
#include <interface/Panel.hh>
#include <interface/menus/InGameMenu.hh>
#include <resources/Text.hh>



Player::Player(const graphics::Color c)
  : _interface(std::make_shared<interface::Interface> (c))
  , _cursor(std::make_shared<interface::Cursor> ())
  , _color(c)
{
  static size_t static_id = 0;
  _id = static_id++;

  _cursor->setColor(c);
  _interface->addElement(_cursor);

  _panel = std::make_shared<interface::Panel> (
    game::Status::battle()->map(), _cursor);
  _interface->addElement(_panel);

  resetCellCursorPosition();
}



void Player::moveCursorUp()
{
  _cursor->moveUp();
  resetCellCursorPosition();
}

void Player::moveCursorDown()
{
  _cursor->moveDown();
  resetCellCursorPosition();
}

void Player::moveCursorLeft()
{
  _cursor->moveLeft();
  resetCellCursorPosition();
}

void Player::moveCursorRight()
{
  _cursor->moveRight();
  resetCellCursorPosition();
}

void Player::resetCellCursorPosition()
{
  _cellCursorPosition = _cursor->coords();
}



void Player::togglePanel()
{
  _panel->toggleStatus();
}



void Player::updatePanelPosition(const graphics::Size2& windowSize)
{
  _panel->setWindowSize(windowSize);
}



void Player::select()
{
  // If there is a unit, which did not play and belong to us, allow to select it
  auto unit(game::Status::battle()->map()->unit(_cursor->coords()));
  if (unit && !unit->played() && unit->playerId() == _id)
  {
    game::Status::pushState(e_state::SELECTION_UNIT);
  }
  else
  {
    const auto coords{_cursor->coords()};
    auto b{game::Status::battle()->map()->getBuilding(coords)};
    if (b && (*b)->faction() == static_cast<int> (_id))
    {
      game::Status::pushState(e_state::BUILDING_MENU);
        game::Status::setStateAttributes(
      std::make_shared<Coords> (coords));
      // std::make_shared<bool> (false));
    }
    else
    {
      game::Status::pushState(e_state::MAP_MENU);
    }
  }
  game::Status::resumeState();
}



void Player::updateSelectedUnit()
{
  game::Status::battle()->map()->selectUnit(_cursor->coords());
}
