/**
 * \file
 * \date November 22, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuildingUnits definition
 */

#include <interface/menus/MenuBuildingUnits.hh>

#include <cassert>
#include <debug/Debug.hh>

#include <context/State.hh>
#include <game/Map.hh>
#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>
#include <interface/Cursor.hh>



namespace interface {


void MenuBuildingUnits::build()
{
  _lock.lock();
  _entries.clear();
  _lock.unlock();

  auto map(game::Status::battle()->map());
  _building = *(map->building(_coords));
  if (_building->units().size() == 0)
  {
    ERROR("MenuBuildingUnits: No Unit in the Building");
    assert(false);
    return;
  }

  size_t i{0u};
  for (auto& mbr: _building->units())
  {
    // Unit statistics
    const auto& unit_data =
      "hp:     " + std::to_string(mbr->hp())
      + '\n' + "attack: " + std::to_string(mbr->attackValue());

    auto entry(std::make_shared<MenuEntry> (
      UNIT_TYPE_STR.at(mbr->type()), *(mbr->sprite()), unit_data));

    entry->setCallbacks( { [=, this] { _building->removeUnit(i); } });

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



void MenuBuildingUnits::draw()
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
