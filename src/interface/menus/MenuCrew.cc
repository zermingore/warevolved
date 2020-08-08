/**
 * \file
 * \date September 7, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuCrew implementation
 */

#include <interface/menus/MenuCrew.hh>

#include <cassert>

#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <interface/Cursor.hh>
#include <interface/menus/MenuEntry.hh>

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
    if (!unit && (_selectedUnit->crewSize() != 0u))
    {
      auto vehicle = std::static_pointer_cast<Vehicle> (_selectedUnit);
      const Coords coords = { _coords.c + 1, _coords.l };
      for (auto& member: vehicle->crew())
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
        entry->setCallbacks(
        {
          [=] { vehicle->dropOff(member.first, coords); },
        });

        _entries.emplace_back(entry);
      }
    }

    if (_selectedUnit->canReceive(unit))
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::PICK_UP));
      entry_group->setCallbacks(
      {
        [=, this] { _selectedUnit->addToCrew(unit); },
        [=] { game::Status::battle()->map()->stashUnit(*unit); },
        [=, this] { game::Status::battle()->map()->moveUnit(_coords); },
        [=, this] { game::Status::player()->cursor()->setCoords(_coords); },
        [=] { game::Status::clearStates(); }
      });
      _entries.emplace_back(entry_group);
    }
    else if (unit->canReceive(_selectedUnit))
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::BOARD));
      entry_group->setCallbacks(
      {
        [=, this] { unit->addToCrew(_selectedUnit); },
        [=, this] { game::Status::battle()->map()->stashUnit(*_selectedUnit); },
        [=, this] { game::Status::player()->cursor()->setCoords(_coords); },
        [=] { game::Status::clearStates(); }
      });
      _entries.emplace_back(entry_group);
    }

    NOTICE("Build crew menu");
  }

  addCancelEntry( [=, this] { cancel(); } );
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
