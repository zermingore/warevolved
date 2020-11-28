/**
 * \file
 * \date November 26, 2020
 * \author Zermingore
 * \brief StateMenu2d definition
 */

#include <context/StateMenu2d.hh>

#include <debug/Debug.hh>

#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/MenuCrewBrowse.hh>
#include <interface/menus/MenuCrewMember.hh>



StateMenu2d::StateMenu2d(
  std::initializer_list<std::unique_ptr<interface::InGameMenu>> args)
  // : _menus{args}
{
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=, this] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=, this] { moveDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=, this] { moveLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=, this] { moveRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=, this] { validate(); });
  _evtMgr->registerEvent(e_input::EXIT,       [=, this] { exit();     });
}


void StateMenu2d::suspend()
{
  /// \todo set menu at optimal coordinates (avoid hiding units for instance)
  // _menuCrewCoords = _menuCrew->coords();
}



void StateMenu2d::resume()
{
  // retrieve coordinates from the attributes
  if (!_attributes.empty())
  {
    fetchAttributes();
  }

  auto x_offset{0u};
  for (const auto& menu: _menus)
  {
    menu->setCoords({_menus[0]->coords().x + x_offset, _menus[0]->coords().y});
    menu->build();
    // menu->setHidden(true);
    x_offset += 4; // in cells
  }

  // _menuCrew->setCoords(_menuCrewCoords);
  // _menuCrew->setConfirmEntryActive(_menuCrewConfirmEntryActive);
  // _menuCrew->build();

  // _menuMemberCoords = _menuCrewCoords;
  // _menuMemberCoords.x += 4; // in cells
  // _menuMember->setCoords(_menuMemberCoords);
  // _menuMember->build();

  // _browseMembers = true;
  // _menuCrew->setActive(true);
  // _menuMember->setActive(false);
  // if (   _menuCrew->currentSelection() == e_entry::CANCEL
  //     || _menuCrew->currentSelection() == e_entry::CREW_CONFIRM)
  // {
  //   _menuMember->setHidden(true);
  // }
  // else
  // {
  //   _menuMember->setUnitIdx(static_cast<int> (_menuCrew->selectedEntry()));
  //   _menuMember->setHidden(false);
  // }
}



void StateMenu2d::moveUp()
{
  _menus[_currentMenu]->decrementSelectedEntry();
  // if (_browseMembers)
  // {
  //   _menuCrew->decrementSelectedEntry();
  //   setFocusMenuMember();
  // }
  // else
  // {
  //   _menuMember->decrementSelectedEntry();
  //   if (_unitIdx != 0)
  //   {
  //     --_unitIdx;
  //   }
  //   else
  //   {
  //     _unitIdx = static_cast<int> (_menuMember->getEntries().size()) - 1;
  //   }
  // }
}



void StateMenu2d::moveDown()
{
  _menus[_currentMenu]->incrementSelectedEntry();

  // if (_browseMembers)
  // {
  //   _menuCrew->incrementSelectedEntry();
  //   setFocusMenuMember();
  // }
  // else
  // {
  //   _menuMember->incrementSelectedEntry();
  //   _unitIdx =
  //     (_unitIdx + 1) % static_cast<int> (_menuMember->getEntries().size());
  // }
}



void StateMenu2d::setFocusNextMenu()
{
  // Hide or reveal the menu depending on the entry we currently hightlight
  if (   _menus[_currentMenu]->currentSelection() == e_entry::CANCEL
      || _menus[_currentMenu]->currentSelection() == e_entry::CONFIRM)
  {
    // _menus[_currentMenu]->setHidden(true);
    --_currentMenu;
  }
  else
  {
    if (static_cast<size_t> (_currentMenu) < _menus.size())
    {
      ++_currentMenu;
      // _menus[_currentMenu]->setHidden(false);
      // _menus[_currentMenu]->setSelectionIdx(_selectionIdx);
    }
  }
}



void StateMenu2d::moveRight()
{
  // No menu right to 'Confirm' and 'Cancel'
  if (   _menus[_currentMenu]->currentSelection() == e_entry::CANCEL
      || _menus[_currentMenu]->currentSelection() == e_entry::CONFIRM)
  {
    return;
  }

  if (static_cast<size_t> (_currentMenu) < _menus.size())
  {
    // _menus[_currentMenu]->setActive(false);
    ++_currentMenu;
    // _menus[_currentMenu]->setActive(true);
    _selectionIdx = 0;
  }
}



void StateMenu2d::moveLeft()
{
  if (_currentMenu > 0)
  {
    // _menus[_currentMenu]->setActive(false);
    --_currentMenu;
    // _menus[_currentMenu]->setActive(true);
    _selectionIdx = 0;
  }
}



void StateMenu2d::validate()
{
  if (_currentMenu == 0)
  {
    if (_menus[_currentMenu]->currentSelection() == e_entry::CANCEL)
    {
      cancel();
      return;
    }

    if (_menus[_currentMenu]->currentSelection() == e_entry::CONFIRM)
    {
      _confirmCallback();
      game::Status::clearStates();
      return;
    }

    moveRight(); // same behaviour
    return;
  }

  if (_menus[_currentMenu]->currentSelection() == e_entry::CANCEL)
  {
    exit();
    return;
  }

  _menus[_currentMenu]->validate();
}



void StateMenu2d::exit() // escape key / cancel entry
{
  if (_currentMenu == 0)
  {
    cancel();
    return;
  }

  if (_currentMenu > 0)
  {
    // ->setActive(false);
    --_currentMenu;
    _menus[_currentMenu]->resetSelectedEntry();
    // ->setActive(true);
  }
}



void StateMenu2d::cancel()
{
  _cancelCallback();

  // auto selectedUnit{game::Status::battle()->map()->selectedUnit()};
  // restore dropped unit
  // auto v = std::static_pointer_cast<Vehicle> (selectedUnit);
  // v->restoreCrew();
  // v->clearDroppedHistory();


  /// \todo game::Status::popCurrentState(); should be enough
  game::Status::popCurrentState();

  // Pop every select_drop_zone and crew_management states
  // while (   game::Status::state() != e_state::ACTION_MENU
  //        && game::Status::state() != e_state::SELECTION_UNIT)
  // {
  //   game::Status::popCurrentState();
  // }
}



void StateMenu2d::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateMenu2d::fetchAttributes called without attributes");
    assert(false);
    return;
  }

  // Base menu coordinates in function of the first one
  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _menus[0]->coords().c = p->c;
  _menus[0]->coords().l = p->l;


  // auto p2 = std::static_pointer_cast<bool> (_attributes[1]);
  // _menuCrewConfirmEntryActive = *p2;

  /// \todo fetch selected and hovered units?

  // reset the attributes vector
  _attributes.clear();
}



void StateMenu2d::draw()
{
  game::Status::player()->cursor()->disableDrawThisFrame();

  auto i{0};
  for (const auto& menu: _menus)
  {
    if (i > _currentMenu)
    {
      break;
    }

    menu->draw();
    ++i;
  }
}
