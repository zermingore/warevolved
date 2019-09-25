/**
 * \file
 * \date September 7, 2019
 * \author Zermingore
 * \brief MenuCrew implementation
 */


#include <interface/menus/MenuCrew.hh>

#include <cassert>

#include <interface/menus/MenuEntry.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <game/PathFinding.hh>

#include <debug/Debug.hh>


namespace interface {



void MenuCrew::build()
{
  auto map(game::Status::battle()->map());
  game::Status::player()->updateSelectedUnit();
  auto unit(map->unit(_coords));

  _selectedUnit = map->selectedUnit();
  assert(_selectedUnit && "Cannot build a MenuCrew without selected unit");
  if (_selectedUnit->playerId() == unit->playerId())
  {
    /// \todo check space available (and allow to select drop location)
    if (_selectedUnit->crewSize())
    {
      auto vehicle = std::static_pointer_cast<Vehicle> (_selectedUnit);
      const Coords coords = { _coords.c + 1, _coords.l };
      for (auto& member: vehicle->getCrew())
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
        entry->setCallbacks(
        { /// \todo forbid move; allow further drops
          [=] { vehicle->dropOff(member.first, coords); },
        });

        _entries.push_back(entry);
      }
    }

    /// \todo check if the vehicle is already full
    if (_selectedUnit->canHaveCrew() && unit->type() == e_unit::SOLDIERS)
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::PICK_UP));
      entry_group->setCallbacks(
      {
        [=] { _selectedUnit->addToCrew(unit); },
        [=] { game::Status::battle()->map()->hideUnit(*unit); },
        [=] { game::Status::battle()->map()->moveUnit(_coords); },
        [=] { game::Status::clearStates(); },
        [=] { game::Status::player()->cursor()->setCoords(_coords); }
      });
      _entries.push_back(entry_group);
    }
    else if (_selectedUnit->type() == e_unit::SOLDIERS && unit->canHaveCrew())
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::BOARD));
      entry_group->setCallbacks(
      {
        [=] { unit->addToCrew(_selectedUnit); },
        [=] { game::Status::battle()->map()->hideUnit(*_selectedUnit); },
        [=] { game::Status::clearStates(); },
        [=] { game::Status::player()->cursor()->setCoords(_coords); }
      });
      _entries.push_back(entry_group);
    }

    NOTICE("Build crew menu");
  }

  addCancelEntry( [=] { cancel(); } );
}



void MenuCrew::cancel()
{
  game::Status::clearStates();
}



void MenuCrew::draw()
{
  InGameMenu::draw();
}


} // namespace interface