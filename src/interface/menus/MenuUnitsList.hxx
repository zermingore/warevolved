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
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <interface/Cursor.hh>
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
    auto map(game::Status::battle()->map());
    auto building = *(map->building(_coords));
    _units = building->units();
  }
  else if (std::is_same<T, Vehicle>::value)
  {
    auto vehicle = std::static_pointer_cast<Vehicle> (
      game::Status::battle()->map()->selectedUnit());
    // _units = vehicle->crew();
  }
  else
  {
    ERROR("MenuUnitsList: Invalid container type");
    return;
  }

  auto map(game::Status::battle()->map());
  if (_units.size() == 0)
  {
    ERROR("MenuUnitsList: No Unit");
    assert(false);
    return;
  }

  size_t i{0u};
  for (auto& mbr: _units)
  {
    // Unit statistics
    const auto& unit_data =
      "hp:     " + std::to_string(mbr->hp())
      + '\n' + "attack: " + std::to_string(mbr->attackValue());

    auto entry(std::make_shared<MenuEntry> (
      UNIT_TYPE_STR.at(mbr->type()), *(mbr->sprite()), unit_data));

    if (std::is_same<T, Building>::value)
    {
      auto building = *(map->building(_coords));
      entry->setCallback([=, this] { building->removeUnit(i); });
    }
    else if (std::is_same<T, Vehicle>::value)
    {
      auto vehicle = std::static_pointer_cast<Vehicle> (
        game::Status::battle()->map()->selectedUnit());
      entry->setCallback([=, this] { vehicle->dropOff(i, _coords); });
    }
    else
    {
      ERROR("MenuUnitsList: Invalid container type");
      return;
    }


    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
    ++i;
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
