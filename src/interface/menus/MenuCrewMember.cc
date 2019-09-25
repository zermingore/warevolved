/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewMember definition
 */


#include <interface/menus/MenuCrewMember.hh>

#include <debug/Debug.hh>

#include <common/enums/states.hh>
#include <context/State.hh>
#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <game/PathFinding.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>


namespace interface {


void MenuCrewMember::build()
{
  auto map(game::Status::battle()->map());
  const auto selectedUnit = map->selectedUnit();
  auto vehicle = std::static_pointer_cast<Vehicle> (selectedUnit);
  _entries.clear();

  // Add a get_out entry only if the unit can exit the vehicle
  PathFinding path(vehicle);
  const auto freeDropZones = path.getDropZones(vehicle->coords());
  if (freeDropZones.size() > 0)
  {
    auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
    entry->setCallbacks(
    { /// \todo forbid move; allow further drops
      [=] { getOut(); },
    });
    _entries.push_back(entry);
  }

  addCancelEntry( [=] { cancel(); } );
}



void MenuCrewMember::draw()
{
  if (_hidden)
  {
    return;
  }

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



void MenuCrewMember::getOut()
{
  auto vehicle_coords(game::Status::battle()->map()->selectedUnit()->coords());

  game::Status::pushState(e_state::SELECT_DROP_ZONE);
  game::Status::currentState()->setAttributes(
    std::make_shared<Coords> (vehicle_coords),
    std::make_shared<e_unit_role> (_role)
  );

  game::Status::currentState()->resume();
}


} // namespace interface