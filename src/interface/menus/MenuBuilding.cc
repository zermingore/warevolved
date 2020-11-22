/**
 * \file
 * \date November 21, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuilding definition
 */

#include <interface/menus/MenuBuilding.hh>

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



void MenuBuilding::build()
{
  auto map(game::Status::battle()->map());
  _building = *(map->getBuilding(_coords));
  if (_building->getUnits().size() == 0)
  {
    ERROR("MenuBuilding: No Unit in the Building");
    return;
  }

  size_t i{0u};
  for ([[maybe_unused]] auto& unused: _building->getUnits())
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::EXIT_BUILDING));
    entry->setCallbacks( { [=, this] { _building->removeUnit(i); } });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
    ++i;
  }

  addCancelEntry( [=, this] { cancel(); } );

  // increase highlight sprite
  using p = graphics::MapGraphicsProperties;
  _imageSelection->setSize(p::cellWidth() * 4, p::cellHeight());
}



void MenuBuilding::cancel()
{
  game::Status::clearStates();
}



void MenuBuilding::draw()
{
  InGameMenu::draw();
}


} // namespace interface
