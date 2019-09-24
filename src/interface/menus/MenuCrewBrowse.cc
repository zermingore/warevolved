/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewBrowse definition
 */


#include <interface/menus/MenuCrewBrowse.hh>

#include <cassert>
#include <debug/Debug.hh>

#include <interface/menus/MenuEntryCrew.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <game/units/Vehicle.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>



namespace interface {



MenuCrewBrowse::MenuCrewBrowse()
{
}



void MenuCrewBrowse::build()
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
      for (auto& mem: vehicle->getCrew())
      {
        auto entry(std::make_shared<MenuEntryCrew> (mem.first, mem.second));
        entry->setCallbacks(
        { /// \todo forbid move; allow further drops
          [=] { vehicle->dropOff(mem.first, coords); },
        });

        _entries.push_back(entry);
      }
    }
  }

  NOTICE("Built MenuCrewBrowse");

  auto entry_confirm(std::make_shared<MenuEntryCrew> (e_entry::CREW_CONFIRM));
  entry_confirm->setCallback( [=] { confirm(); });
  _entries.push_back(entry_confirm);

  auto entry_cancel(std::make_shared<MenuEntryCrew> (e_entry::CANCEL));
  entry_cancel->setCallback( [=] { cancel(); });
  _entries.push_back(entry_cancel);
}



void MenuCrewBrowse::cancel()
{
  game::Status::clearStates();
}


void MenuCrewBrowse::confirm()
{
  WARNING("Confirming");

 _selectedUnit->setPlayed(true);
  game::Status::clearStates();
}



void MenuCrewBrowse::draw()
{
  update();

  for (auto entry: _entries)
  {
    entry->draw();
  }

  if (_active)
  {
    _imageSelection->draw();
  }
}


} // namespace interface
