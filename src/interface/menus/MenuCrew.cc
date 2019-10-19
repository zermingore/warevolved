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
    if (!unit && _selectedUnit->crewSize())
    {
      auto vehicle = std::static_pointer_cast<Vehicle> (_selectedUnit);
      const Coords coords = { _coords.c + 1, _coords.l };
      for (auto& member: vehicle->crew())
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
        entry->setCallbacks(
        {
          [=, this] { vehicle->dropOff(member.first, coords); },
        });

        _entries.push_back(entry);
      }
    }

    /// \todo check if the vehicle is already full
    if (_selectedUnit->canHaveCrew() && unit->type() == e_unit::SOLDIER)
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::PICK_UP));
      entry_group->setCallbacks(
      {
        [=, this] { _selectedUnit->addToCrew(unit); },
        [=, this] { game::Status::battle()->map()->stashUnit(*unit); },
        [=, this] { game::Status::battle()->map()->moveUnit(_coords); },
        [=, this] { game::Status::clearStates(); },
        [=, this] { game::Status::player()->cursor()->setCoords(_coords); }
      });
      _entries.push_back(entry_group);
    }
    else if (_selectedUnit->type() == e_unit::SOLDIER && unit->canHaveCrew())
    {
      auto entry_group(std::make_shared<MenuEntry> (e_entry::BOARD));
      entry_group->setCallbacks(
      {
        [=, this] { unit->addToCrew(_selectedUnit); },
        [=, this] { game::Status::battle()->map()->stashUnit(*_selectedUnit); },
        [=, this] { game::Status::clearStates(); },
        [=, this] { game::Status::player()->cursor()->setCoords(_coords); }
      });
      _entries.push_back(entry_group);
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
