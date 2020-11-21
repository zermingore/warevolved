/**
 * \file
 * \date November 21, 2020
 * \author Zermingore
 * \namespace interface
 * \brief MenuBuildingUnit definition
 */

#include <interface/menus/MenuBuildingUnit.hh>

#include <cassert>
#include <context/State.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Battle.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <game/Terrain.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <interface/Cursor.hh>

namespace interface {


void MenuBuildingUnit::build()
{
  _lock.lock();
  _entries.clear();
  _lock.unlock();


  auto map(game::Status::battle()->map());
  ///< \todo avoid using Menu's coordinates
  auto building = *(map->getBuilding(_coords));
  assert(building && building->getUnits().size() > 0);

  // Find building doors
  bool available_door = false;
  for (const auto coords: building->getCoords())
  {
    auto c = map->cell(*coords);
    if (c->terrain() == e_terrain::BUILDING_DOOR && !c->unit())
    {
      available_door = true;
      break;
    }
  }

  if (available_door)
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
    entry->setCallbacks(
    {
      [=, this] { getOut(); },
    });

    _lock.lock();
    _entries.emplace_back(std::move(entry));
    _lock.unlock();
  }

  addCancelEntry( [=, this] { cancel(); } );
}



void MenuBuildingUnit::draw()
{
  if (_hidden)
  {
    return;
  }

  update();

  _lock.lock();
  for (const auto& entry: _entries)
  {
    entry->draw();
  }
  _lock.unlock();

  if (_active)
  {
    _imageSelection->draw();
  }
}



void MenuBuildingUnit::getOut()
{
  auto coords(game::Status::player()->cellCursorPosition());

  game::Status::pushState(e_state::SELECT_EXIT_ZONE);
  game::Status::setStateAttributes(
    std::make_shared<Coords> (coords),
    std::make_shared<size_t> (_unitIdx)
  );

  game::Status::resumeState();
}


} // namespace interface
