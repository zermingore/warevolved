/**
 * \file
 * \date November 30, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuUnitsList template definitions
 */

#include <interface/menus/MenuUnitsList.hh>

#include <cassert>
#include <debug/Debug.hh>

#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Building.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <interface/menus/MenuEntry.hh>



namespace interface {


template<typename T>
void MenuUnitsList<T>::build()
{
  _lock.lock();
  _entries.clear();
  _lock.unlock();

  if (std::is_same<T, Building>::value)
  {
    buildEntriesBuilding();
  }
  else if (std::is_same<T, Vehicle>::value)
  {
    buildEntriesVehicle();
  }
  else
  {
    ERROR("MenuUnitsList: Invalid container type");
    return;
  }

  if (_confirmActive)
  {
    auto entry_confirm(std::make_shared<MenuEntry> (e_entry::CONFIRM, true));
    entry_confirm->setCallback( [=, this] { confirm(); });
    _lock.lock();
    _entries.emplace_back(std::move(entry_confirm));
    _lock.unlock();
  }

  auto entry_cancel(std::make_shared<MenuEntry> (e_entry::CANCEL, true));
  entry_cancel->setCallback( [=, this] { cancel(); });
  _lock.lock();
  _entries.emplace_back(std::move(entry_cancel));
  _lock.unlock();

  // increase highlight sprite
  using p = graphics::MapGraphicsProperties;
  _imageSelection->setSize(p::cellWidth() * 4, p::cellHeight());
}



template<typename T>
void MenuUnitsList<T>::buildEntriesBuilding()
{
  auto building = *(game::Status::battle()->map()->building(_coords));

  size_t i{0u};
  for (auto& mbr: building->units())
  {
    // Unit attributes
    const auto& unit_data =
      "hp:     " + std::to_string(mbr->hp())
      + '\n' + "attack: " + std::to_string(mbr->attackValue());

    auto entry(std::make_shared<MenuEntry> (
      UNIT_TYPE_STR.at(mbr->type()), *(mbr->sprite()), unit_data));

    entry->setCallback([=, this] { building->removeUnit(i); });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
    ++i;
  }
}



template<typename T>
void MenuUnitsList<T>::buildEntriesVehicle()
{
  game::Status::player()->updateSelectedUnit();
  auto selectedUnit{ game::Status::battle()->map()->selectedUnit() };
  assert(selectedUnit && "MenuUnitList<Vehicle>: No selected unit");
  if (!selectedUnit->canHaveCrew())
  {
    return;
  }

  auto vehicle = std::static_pointer_cast<Vehicle> (selectedUnit);
  if (vehicle->crewSize() != 0u)
  {
    size_t i{0u};
    for (auto& mbr: vehicle->crew())
    {
      // Unit attributes
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



template<typename T>
void MenuUnitsList<T>::confirm()
{
  game::Status::clearStates();
}



template<typename T>
void MenuUnitsList<T>::draw()
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
