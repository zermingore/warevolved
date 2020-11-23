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
#include <interface/menus/MenuBuildingUnits.hh>



StateMenuBuilding::StateMenuBuilding()
  : _menuUnitsCoords(0, 0)
  , _browseUnits(true)
{
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=, this] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=, this] { moveDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=, this] { moveLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=, this] { moveRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=, this] { validate(); });
  _evtMgr->registerEvent(e_input::EXIT,       [=, this] { exit();     });

  _menuUnits = std::make_unique<interface::MenuBuildingUnits> ();
  _menuUnit = std::make_unique<interface::MenuBuildingUnit> ();
}



void StateMenuBuilding::suspend()
{
  /// \todo set menu at optimal coordinates (avoid hiding units for instance)
  _menuUnitsCoords = _menuUnits->coords();
}



void StateMenuBuilding::resume()
{
  // retrieve coordinates from the attributes
  if (!_attributes.empty())
  {
    fetchAttributes();
  }

  _menuUnits->setCoords(_menuUnitsCoords);
  _menuUnits->setConfirmEntryActive(_menuBuildingConfirmEntryActive);
  _menuUnits->build();

  _menuUnitCoords = _menuUnitsCoords;
  _menuUnitCoords.x += 4; // in cells
  _menuUnit->setCoords(_menuUnitCoords);
  _menuUnit->build();

  _browseUnits = true;
  _menuUnits->setActive(true);
  _menuUnit->setActive(false);
  if (   _menuUnits->currentSelection() == e_entry::CANCEL
      || _menuUnits->currentSelection() == e_entry::EXIT_BUILDING)
  {
    _menuUnit->setHidden(true);
  }
  else
  {
    auto pe = _menuUnits->getEntries()[_menuUnits->selectedEntry()];
    auto e = std::static_pointer_cast<interface::MenuEntry> (pe);
    _menuUnit->setHidden(false);
  }
}



void StateMenuBuilding::moveUp()
{
  if (_browseUnits)
  {
    _menuUnits->decrementSelectedEntry();
    setFocusMenuUnit();
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
    _menuUnits->incrementSelectedEntry();
    setFocusMenuUnit();
  }
  else
  {
    _menuUnit->incrementSelectedEntry();
    _unitIdx =
      (_unitIdx + 1) % static_cast<int> (_menuUnit->getEntries().size());
  }
}



void StateMenuBuilding::setFocusMenuUnit()
{
  // Hide or reveal the menu depending on the entry we currently hightlight
  if (_menuUnits->currentSelection() == e_entry::CANCEL)
  {
    _menuUnit->setHidden(true);
  }
  else
  {
    // Retrieve the Unit matching the highlighted entry
    auto pe = _menuUnits->getEntries()[_menuUnits->selectedEntry()];
    auto e = std::static_pointer_cast<interface::MenuEntry> (pe);
    _menuUnit->setHidden(false);
    _menuUnit->setUnitIdx(_unitIdx);
  }
}



void StateMenuBuilding::moveRight()
{
  // No member menu next to 'Confirm' and 'Cancel'
  if (   _menuUnits->currentSelection() == e_entry::CANCEL
      || _menuUnits->currentSelection() == e_entry::EXIT_BUILDING)
  {
    return;
  }

  _browseUnits = false;
  _menuUnit->setActive(true);
  _menuUnits->setActive(false);
}



void StateMenuBuilding::moveLeft()
{
  _browseUnits = true;
  _menuUnits->setActive(true);
  _menuUnit->setActive(false);
  _menuUnit->resetSelectedEntry();
}



void StateMenuBuilding::validate()
{
  if (_browseUnits)
  {
    if (_menuUnits->currentSelection() == e_entry::CREW_CONFIRM)
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

  if (_menuUnit->currentSelection() == e_entry::CANCEL)
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
    _menuUnits->setActive(true);
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
  _menuUnitsCoords.c = p->c;
  _menuUnitsCoords.l = p->l;

  _menuUnitCoords = _menuUnitsCoords;
  _menuUnitCoords.x += 4; // in cells

  _menuUnits->setCoords(*p);
  _menuUnit->setCoords(*p);

  auto p2 = std::static_pointer_cast<bool> (_attributes[1]);
  _menuBuildingConfirmEntryActive = *p2;

  // reset the attributes vector
  _attributes.clear();
}



void StateMenuBuilding::draw()
{
  game::Status::player()->cursor()->disableDrawThisFrame();
  _menuUnits->draw();
  _menuUnit->draw();
}
