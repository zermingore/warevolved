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
#include <interface/menus/MenuEntry.hh>



namespace interface {


void MenuCrewBrowse::build()
{
  auto map(game::Status::battle()->map());
  game::Status::player()->updateSelectedUnit();

  _lock.lock();
  _entries.clear();
  _lock.unlock();

  _selectedUnit = map->selectedUnit();
  assert(_selectedUnit && "Cannot build a MenuCrew without selected unit");
  if (_selectedUnit->canHaveCrew())
  {
    auto vehicle = std::static_pointer_cast<Vehicle> (_selectedUnit);
    if (vehicle->crewSize() != 0u)
    {
      size_t i{0u};
      for (auto& mbr: vehicle->crew())
      {
        // Unit statistics
        const auto& unit_data =
          "hp:     " + std::to_string(mbr.second->hp())
          + '\n' + "attack: " + std::to_string(mbr.second->attackValue());

        auto entry(std::make_shared<MenuEntry> (
          UNIT_ROLE_STR.at(mbr.first), *(mbr.second->sprite()), unit_data));

        entry->setCallbacks(
        {
          [=, this] { vehicle->dropOff(i, _coords); }
        });

        _lock.lock();
        _entries.emplace_back(std::move(entry));
        _lock.unlock();
        ++i;
      }
    }
  }

  if (_confirmEntryActive)
  {
    auto entry_confirm(
      std::make_shared<MenuEntry> (e_entry::CREW_CONFIRM, true));
    entry_confirm->setCallback( [=, this] { confirm(); });

    _lock.lock();
    _entries.emplace_back(std::move(entry_confirm));
    _lock.unlock();
  }

  auto entry_cancel(
    std::make_shared<MenuEntry> (e_entry::CANCEL, true));
  entry_cancel->setCallback( [=, this] { cancel(); });

  _lock.lock();
  _entries.emplace_back(std::move(entry_cancel));
  _lock.unlock();

  // increase highlight sprite
  using p = graphics::MapGraphicsProperties;
  _imageSelection->setSize(p::cellWidth() * 4, p::cellHeight());
}



void MenuCrewBrowse::confirm()
{
 _selectedUnit->setPlayed(true);
  game::Status::clearStates();
}



void MenuCrewBrowse::draw()
{
  update();

  _lock.lock();
  for (const auto& entry: _entries)
  {
    entry->draw();
  }
  _lock.unlock();

  _imageSelection->draw();
}


} // namespace interface
