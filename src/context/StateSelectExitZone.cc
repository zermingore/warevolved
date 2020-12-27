/**
 * \file
 * \date September 24, 2019
 * \author Zermingore
 * \brief StateSelectExitZone class definition
 */

#include <context/StateSelectExitZone.hh>

#include <debug/Debug.hh>

#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Vehicle.hh>
#include <game/Terrain.hh>
#include <graphics/Properties.hh>
#include <graphics/graphic_types.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>



void StateSelectExitZone::fetchAttributes()
{
  if (_attributes.empty())
  {
    ERROR("StateSelectExitZone::fetchAttributes called without attributes");
    assert(false);
    return;
  }

  auto pCoords = std::static_pointer_cast<Coords> (_attributes[0]);
  _buildingLocation.c = pCoords->c;
  _buildingLocation.l = pCoords->l;

  _unitIdx = *(std::static_pointer_cast<size_t> (_attributes[1]));

  // reset the attributes vector
  _attributes.clear();
}



void StateSelectExitZone::resume()
{
  // retrieve coordinates from the attributes
  if (!_attributes.empty()) {
    fetchAttributes();
  }

  auto map(game::Status::battle()->map());
  _building = *(map->building(_buildingLocation));
  assert(_building && _building->units().size() > 0);

  // Find building doors
  for (const auto coords: _building->getCoords())
  {
    auto c = map->cell(*coords);
    if (c->terrain() == e_terrain::BUILDING_DOOR && !c->unit())
    {
      _cells.emplace_back(c);
    }
  }

  _unit = _building->units()[_unitIdx];

  assert(!_cells.empty() && "StateSelectExitZone: no exit zone available");
}



void StateSelectExitZone::draw()
{
  if (_cells.empty())
  {
    ERROR("No exit zone to select");
    return;
  }
  if (_indexSelect >= _cells.size())
  {
    ERROR("Invalid exit zone index", _indexSelect, "size:", _cells.size());
    return;
  }

  using p = graphics::Properties;

  game::Status::player()->cursor()->disableDrawThisFrame();

  std::shared_ptr<Map> map = game::Status::battle()->map();

  _holoUnit = std::make_shared<graphics::Sprite> (_unit->sprite()->texture());

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

  // Exit cell coordinates
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



void StateSelectExitZone::validate()
{
  auto map(game::Status::battle()->map());

  // Find building doors
  std::vector<Coords> doors;
  for (const auto c: (_building)->getCoords())
  {
    if (map->cell(*c)->terrain() == e_terrain::BUILDING_DOOR)
    {
      doors.emplace_back(*c);
    }
  }

  _unit->setCoords(doors[_indexSelect]);
  map->stashPopUnit(*_unit);
  _building->removeUnit(_unitIdx);

  game::Status::clearStates();
}
