/**
 * \file
 * \date September 24, 2019
 * \author Zermingore
 * \brief StateSelectDropZone class definition
 */

#include <context/StateSelectDropZone.hh>

#include <debug/Debug.hh>

#include <common/enums/input.hh>
#include <game/Status.hh>
#include <common/enums/attack_result.hh>
#include <input/EventManager.hh>
#include <interface/Cursor.hh>
#include <game/Battle.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Player.hh>
#include <game/PathFinding.hh>
#include <game/units/Vehicle.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/graphic_types.hh>



StateSelectDropZone::StateSelectDropZone()
  : State()
  , _indexZone(0)
{
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=] { selectNextZone();     });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=] { selectPreviousZone(); });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=] { selectPreviousZone(); });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=] { selectNextZone();     });
  _evtMgr->registerEvent(e_input::SELECTION,  [=] { validate();           });
  _evtMgr->registerEvent(e_input::EXIT,       [=] { exit();               });

  // Graphical attributes initialization
  _zoneHighlight = std::make_shared<graphics::Sprite> ("cursor");
  _zoneHighlight->setColor(graphics::Color(255, 127, 127, 255));

  using p = graphics::MapGraphicsProperties;

  // explicitly using some floats for the division
  float x(static_cast<float> (_zoneHighlight->texture()->getSize().x));
  float y(static_cast<float> (_zoneHighlight->texture()->getSize().y));
  _zoneHighlight->setScale(p::cellWidth()  / x, p::cellHeight() / y);
  _zoneHighlight->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  /// \todo hard-coded soldiers
  _holoUnit = std::make_shared<graphics::Sprite> ("soldiers");
  _holoUnit->setColor(graphics::Color(127, 255, 127, 255));

  x = static_cast<float> (_holoUnit->texture()->getSize().x);
  y = static_cast<float> (_holoUnit->texture()->getSize().y);
  _holoUnit->setScale(p::cellWidth() / x, p::cellHeight() / y);
}



void StateSelectDropZone::fetchAttributes()
{
  if (!_attributes.size())
  {
    ERROR("fetchAttributes called without available attributes");
    assert(false && "No attribute found");
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _vehicleLocation.c = p->c;
  _vehicleLocation.l = p->l;

  // reset the attributes vector
  _attributes.clear();
}



void StateSelectDropZone::resume()
{
  // retrieve attack coordinates from the attributes
  if (_attributes.size()) {
    fetchAttributes();
  }

  // we need a selected unit to continue
  game::Status::player()->updateSelectedUnit();
  auto selected_unit(game::Status::battle()->map()->selectedUnit());

  PathFinding path(selected_unit);
  _zones = path.getDropZones(_vehicleLocation);

  assert(!_zones.empty() && "StateSelectDropZone: no drop zone available");
}



void StateSelectDropZone::draw()
{
  auto selected_unit(game::Status::battle()->map()->selectedUnit());
  PathFinding path(selected_unit);
  _zones = path.getDropZones(_vehicleLocation);

  if (!_zones.size())
  {
    ERROR("No drop zone to select");
    return;
  }
  if (_indexZone > _zones.size())
  {
    ERROR("Invalid drop zone index", _indexZone, "size:", _zones.size());
    return;
  }

  _holoUnit->drawAtCell(_vehicleLocation);

  // emphasis (scale and rotation) of the cursor over the zone
  static float scale_factor = 1;
  static size_t angle = 0;
  angle % 360 > 180 ? scale_factor -= 0.001f : scale_factor += 0.001f;
  ++angle; // \todo angle will overflow

  using p = graphics::MapGraphicsProperties;
  auto width(p::cellWidth());
  auto height(p::cellHeight());

  // Drop cell coordinates
  auto coords(_zones[_indexZone]->coords());
  auto pos_c(static_cast<float> (coords.c) * width
             + p::gridOffsetX() + width  / 2);
  auto pos_l(static_cast<float> (coords.l) * height
             + p::gridOffsetY() + height / 2);

  _zoneHighlight->setPosition(pos_c, pos_l);
  _zoneHighlight->setRotation(static_cast<float> (angle));

  _zoneHighlight->draw();
}



void StateSelectDropZone::selectPreviousZone()
{
  if (_indexZone == 0)
  {
    _indexZone = _zones.size() - 1;
    return;
  }

  --_indexZone;
}



void StateSelectDropZone::selectNextZone()
{
  _indexZone = (_indexZone + 1) % _zones.size();
}



void StateSelectDropZone::validate()
{
  auto map(game::Status::battle()->map());

  // map->moveUnit(_vehicleLocation);
  // game::Status::battle()->map()->selectedUnit()->setPlayed(true);

  auto unit = game::Status::battle()->map()->unit(_vehicleLocation);
  auto vehicle = std::static_pointer_cast<Vehicle> (unit);

  vehicle->dropOff(e_unit_role::DRIVER, _zones[_indexZone]->coords());

  // Should lock the draw ? (without unlocking it ?)
  game::Status::player()->cursor()->setCoords(_vehicleLocation);

  game::Status::popCurrentState();
  game::Status::currentState()->resume();
}



void StateSelectDropZone::exit()
{
  game::Status::popCurrentState();
}
