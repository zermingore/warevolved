/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \namespace interface
 * \brief MenuCrewBrowse definition
 */

#include <interface/menus/MenuCrewBrowse.hh>

#include <cassert>
#include <debug/Debug.hh>

#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <interface/Cursor.hh>
#include <interface/menus/MenuEntryCrew.hh>



namespace interface {


void MenuCrewBrowse::build()
{
  auto map(game::Status::battle()->map());
  game::Status::player()->updateSelectedUnit();
  auto unit(map->unit(_coords));
  _entries.clear();

  _selectedUnit = map->selectedUnit();
  assert(_selectedUnit && "Cannot build a MenuCrew without selected unit");
  if (_selectedUnit->canHaveCrew())
  {
    auto vehicle = std::static_pointer_cast<Vehicle> (_selectedUnit);
    if (vehicle->crewSize() != 0u)
    {
      int i{0};
      for ([[maybe_unused]] auto& unused: vehicle->crew())
      {
        auto entry(std::make_shared<MenuEntryCrew> (e_entry::NONE, i));
        entry->setCallbacks(
        {
          [=, this] { vehicle->dropOff(i, _coords); }
        });
        _entries.emplace_back(entry);
        ++i;
      }
    }
  }

  if (_confirmEntryActive)
  {
    auto entry_confirm(std::make_shared<MenuEntryCrew> (e_entry::CREW_CONFIRM));
    entry_confirm->setCallback( [=, this] { confirm(); });
    _entries.emplace_back(entry_confirm);
  }
  _confirmEntryActive = true;

  auto entry_cancel(std::make_shared<MenuEntryCrew> (e_entry::CANCEL));
  entry_cancel->setCallback( [=, this] { cancel(); });
  _entries.emplace_back(entry_cancel);

  // increase highlight sprite
  using namespace graphics;
  using p = MapGraphicsProperties;
  _imageSelection->setSize(p::cellWidth() * 4, p::cellHeight());
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

  for (const auto& entry: _entries)
  {
    entry->draw();
  }

  if (_active)
  {
    _imageSelection->draw();
  }
}


} // namespace interface
