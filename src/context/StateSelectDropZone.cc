/**
 * \file
 * \date September 24, 2019
 * \author Zermingore
 * \brief StateSelectDropZone class definition
 */

#include <context/StateSelectDropZone.hh>

#include <debug/Debug.hh>

#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/graphic_types.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>



StateSelectDropZone::StateSelectDropZone()
  : _role(e_unit_role::NONE)
{
}



void StateSelectDropZone::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateSelectDropZone::fetchAttributes called without attributes");
    assert(false);
    return;
  }

  auto pCoords = std::static_pointer_cast<Coords> (_attributes[0]);
  _vehicleLocation.c = pCoords->c;
  _vehicleLocation.l = pCoords->l;

  auto pRole = std::static_pointer_cast<e_unit_role> (_attributes[1]);
  _role = *pRole;

  auto pUnitIndex = std::static_pointer_cast<size_t> (_attributes[2]);
  _unitIdx = *pUnitIndex;

  // reset the attributes vector
  _attributes.clear();
}



void StateSelectDropZone::resume()
{
  // retrieve attack coordinates from the attributes
  if (!_attributes.empty()) {
    fetchAttributes();
  }

  // we need a selected unit to continue
  game::Status::player()->updateSelectedUnit();
  auto selected_unit(game::Status::battle()->map()->selectedUnit());

  PathFinding path(selected_unit);
  _cells = path.getDropZones(_vehicleLocation);

  assert(!_cells.empty() && "StateSelectDropZone: no drop zone available");
}



void StateSelectDropZone::draw()
{
  if (_cells.empty())
  {
    ERROR("No drop zone to select");
    return;
  }
  if (_indexSelect >= _cells.size())
  {
    ERROR("Invalid drop zone index", _indexSelect, "size:", _cells.size());
    return;
  }

  using p = graphics::MapGraphicsProperties;

  game::Status::player()->cursor()->disableDrawThisFrame();

  std::shared_ptr<Map> map = game::Status::battle()->map();
  auto selected_unit(map->selectedUnit());

  auto vehicle{std::static_pointer_cast<Vehicle> (selected_unit)};
  std::shared_ptr<Unit> drop = vehicle->crew()[_unitIdx].second;
  _holoUnit = std::make_shared<graphics::Sprite> (drop->sprite()->texture());

  const auto x = static_cast<float> (_holoUnit->texture()->getSize().x);
  const auto y = static_cast<float> (_holoUnit->texture()->getSize().y);
  _holoUnit->setScale(p::cellWidth() / x, p::cellHeight() / y);

  _holoUnit->drawAtCell(_cells[_indexSelect]->coords());
  _holoUnit->setColor({ 255, 255, 255, 127 });

  // emphasis (rotation) of the cursor over the zone
  static size_t angle = 0;
  angle = (angle + 1) % 360;

  auto width(p::cellWidth());
  auto height(p::cellHeight());

  // Drop cell coordinates
  auto coords(_cells[_indexSelect]->coords());
  auto pos_c(static_cast<float> (coords.c) * width
             + p::gridOffsetX() + width  / 2);
  auto pos_l(static_cast<float> (coords.l) * height
             + p::gridOffsetY() + height / 2);

  _selectHighlight->setPosition(pos_c, pos_l);
  _selectHighlight->setRotation(static_cast<float> (angle));

  for (auto& cell: _cells)
  {
    (*map)[cell->c()][cell->l()]->setHighlight(true);
    (*map)[cell->c()][cell->l()]->setHighlightColor(graphics::Color::Green);
  }
}



void StateSelectDropZone::validate()
{
  auto unit{game::Status::battle()->map()->unit(_vehicleLocation)};
  auto vehicle{std::static_pointer_cast<Vehicle> (unit)};
  vehicle->dropOff(_unitIdx, _cells[_indexSelect]->coords());

  // Should lock the draw ? (without unlocking it ?)
  game::Status::player()->cursor()->setCoords(_vehicleLocation);

  game::Status::pushState(e_state::CREW_MANAGEMENT);
  game::Status::setStateAttributes(
    std::make_shared<Coords> (_vehicleLocation),
    std::make_shared<bool> (true));
  game::Status::resumeState();
}
