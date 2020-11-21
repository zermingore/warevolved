/**
 * \file
 * \date November 20, 2020
 * \author Zermingore
 * \brief StateMenuBuilding definition
 */

#include <context/StateMenuBuilding.hh>

#include <debug/Debug.hh>

#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/Player.hh>
#include <game/units/Unit.hh>
#include <game/Building.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/MenuBuilding.hh>
#include <interface/menus/MenuBuildingUnit.hh>



StateMenuBuilding::StateMenuBuilding()
  : _menuBuildingCoords(0, 0)
  , _browseUnits(true)
{
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=, this] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=, this] { moveDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=, this] { moveLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=, this] { moveRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=, this] { validate(); });
  _evtMgr->registerEvent(e_input::EXIT,       [=, this] { exit();     });

  _menuBuilding = std::make_unique<interface::MenuBuilding> ();
  _menuUnit = std::make_unique<interface::MenuBuildingUnit> ();
}



void StateMenuBuilding::suspend()
{
  /// \todo set menu at optimal coordinates (avoid hiding units for instance)
  _menuBuildingCoords = _menuBuilding->coords();
}



void StateMenuBuilding::resume()
{
  // retrieve coordinates from the attributes
  if (!_attributes.empty())
  {
    fetchAttributes();
  }

  _menuBuilding->setCoords(_menuBuildingCoords);
  _menuBuilding->build();

  _menuUnitsCoords = _menuBuildingCoords;
  _menuUnitsCoords.x += 4; // in cells
  _menuUnit->setCoords(_menuUnitsCoords);
  _menuUnit->build();

  _browseUnits = true;
  _menuBuilding->setActive(true);
  _menuUnit->setActive(false);
  if (   _menuBuilding->getCurrentSelection() == e_entry::CANCEL
      || _menuBuilding->getCurrentSelection() == e_entry::CREW_CONFIRM)
  {
    _menuUnit->setHidden(true);
  }
  else
  {
    auto pe = _menuBuilding->getEntries()[_menuBuilding->selectedEntry()];
    auto e = std::static_pointer_cast<interface::MenuEntry> (pe);
    _menuUnit->setHidden(false);
  }
}



void StateMenuBuilding::moveUp()
{
  if (_browseUnits)
  {
    _menuBuilding->decrementSelectedEntry();
    setFocusMenuMember();
  }
  else
  {
    _menuUnit->decrementSelectedEntry();
    if (_unitIdx != 0)
    {
      --_unitIdx;
    }
    else
    {
      _unitIdx = static_cast<int> (_menuUnit->getEntries().size()) - 1;
    }
  }
}



void StateMenuBuilding::moveDown()
{
  if (_browseUnits)
  {
    _menuBuilding->incrementSelectedEntry();
    setFocusMenuMember();
  }
  else
  {
    _menuUnit->incrementSelectedEntry();
    _unitIdx =
      (_unitIdx + 1) % static_cast<int> (_menuUnit->getEntries().size());
  }
}



void StateMenuBuilding::setFocusMenuMember()
{
  // Hide or reveal the menu depending on the entry we currently hightlight
  if (_menuBuilding->getCurrentSelection() == e_entry::CANCEL)
  {
    _menuUnit->setHidden(true);
  }
  else
  {
    // Retrieve the Unit matching the highlighted entry
    auto pe = _menuBuilding->getEntries()[_menuBuilding->selectedEntry()];
    auto e = std::static_pointer_cast<interface::MenuEntry> (pe);
    _menuUnit->setHidden(false);
    _menuUnit->setUnitIdx(_unitIdx);
  }
}



void StateMenuBuilding::moveRight()
{
  // No member menu next to 'Confirm' and 'Cancel'
  if (   _menuBuilding->getCurrentSelection() == e_entry::CANCEL
      || _menuBuilding->getCurrentSelection() == e_entry::CREW_CONFIRM)
  {
    return;
  }

  _browseUnits = false;
  _menuUnit->setActive(true);
  _menuBuilding->setActive(false);
}



void StateMenuBuilding::moveLeft()
{
  _browseUnits = true;
  _menuBuilding->setActive(true);
  _menuUnit->setActive(false);
  _menuUnit->resetSelectedEntry();
}



void StateMenuBuilding::validate()
{
  if (_browseUnits)
  {
    if (_menuBuilding->getCurrentSelection() == e_entry::CREW_CONFIRM)
    {
      auto selectedUnit{game::Status::battle()->map()->selectedUnit()};
      selectedUnit->setPlayed(true);

      // auto v = std::static_pointer_cast<Building> (selectedUnit);
      // v->clearDroppedHistory();

      game::Status::clearStates();
      return;
    }

    moveRight(); // same behaviour
    return;
  }

  if (_menuUnit->getCurrentSelection() == e_entry::CANCEL)
  {
    exit();
    return;
  }

  _menuUnit->validate();
}



void StateMenuBuilding::exit() // escape key
{
  if (!_browseUnits)
  {
    _browseUnits = true;
    _menuBuilding->setActive(true);
    _menuUnit->setActive(false);
    _menuUnit->resetSelectedEntry();
    return;
  }

  game::Status::clearStates();
}



void StateMenuBuilding::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateMenuBuilding fetchAttributes called without attributes");
    assert(false);
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _menuBuildingCoords.c = p->c;
  _menuBuildingCoords.l = p->l;

  _menuUnitsCoords = _menuBuildingCoords;
  _menuUnitsCoords.x += 4; // in cells

  // auto p2 = std::static_pointer_cast<bool> (_attributes[1]);
  // _menuCrewConfirmEntryActive = *p2;

  // reset the attributes vector
  _attributes.clear();
}



void StateMenuBuilding::draw()
{
  game::Status::player()->cursor()->disableDrawThisFrame();
  _menuBuilding->draw();
  _menuUnit->draw();
}
