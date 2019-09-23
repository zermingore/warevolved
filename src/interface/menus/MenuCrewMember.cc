/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewMember definition
 */


#include <interface/menus/MenuCrewMember.hh>

#include <debug/Debug.hh>

#include <game/Battle.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>


namespace interface {


void MenuCrewMember::build()
{
  auto map(game::Status::battle()->map());
  auto unit(map->unit(_coords));

  const auto selectedUnit = map->selectedUnit();
  auto vehicle = std::static_pointer_cast<Vehicle> (selectedUnit);

  auto entry(std::make_shared<MenuEntry> (e_entry::GET_OUT));
  entry->setCallbacks(
  { /// \todo forbid move; allow further drops
    [=] { /* vehicle->dropOff(member.first, coords); */ },
  });

  _entries.push_back(entry);

  addCancelEntry( [=] { cancel(); } );
}



void MenuCrewMember::draw()
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
