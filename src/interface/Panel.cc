/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side Panel class definition
 */


#include <interface/Panel.hh>

#include <algorithm> // std:min

#include <debug/Debug.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/PathFinding.hh> // e_direction enum
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <game/units/Vehicle.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Properties.hh>
#include <graphics/graphic_types.hh>
#include <interface/Cursor.hh>
#include <interface/MiniMap.hh>
#include <resources/Text.hh>
#include <tools/Fps.hh>



namespace interface {


Panel::Panel(std::shared_ptr<const Map> map,
             std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("side_panel")
  , _map(map)
  , _playerCursor(cursor)
  , _background(std::make_unique<graphics::Sprite> (_imgName))
  , _frameCell(std::make_unique<graphics::Sprite> ("frame_thumbnail"))
  , _frameUnit(std::make_unique<graphics::Sprite> ("frame_thumbnail"))
  , _status(e_panel_status::DEACTIVATED)
  , _fontSize(20)
  , _dateWidth(0)
{
  using namespace graphics;
  setWindowSize(static_cast<Size2> (GraphicsEngine::windowSize()));
  Size2 size { _size.x - _margin * 2, _size.y / 4 };
  _minimap = std::make_unique<MiniMap> (size, map, cursor);
}



void Panel::setWindowSize(const graphics::Size2& size)
{
  _size.x = size.x / 4;
  _size.y = size.y;

  if (_status != e_panel_status::DEACTIVATED)
  {
    computePosition();
  }
}



void Panel::toggleStatus()
{
  _status = static_cast<e_panel_status> (
    (static_cast<int> (_status) + 1)
    % static_cast<int> (e_panel_status::NB_PANEL_STATUS));

  computePosition();
}



void Panel::computePosition()
{
  graphics::Pos2 background_position;
  auto draw_offset(0.f); // rendering room offset
  switch (_status)
  {
    case e_panel_status::POSITION_LEFT:
      draw_offset = _size.x;
      break;

    case e_panel_status::POSITION_RIGHT:
      draw_offset = -_size.x;
      background_position.x = 3.f * _size.x;
      break;

    case e_panel_status::DEACTIVATED:
      break;

    default:
      ERROR("Unexpected panel position");
      assert(false);
      break;
  }

  _background->setPosition(background_position);
  _background->setSize(_size);


  // Terrain
  _frameCell->setPosition(background_position.x + _margin, _margin);

  // Unit
  _frameUnit->setPosition(background_position.x + _margin,
                          _frameCell->size().y + 4 * _margin);

  // MiniMap
  _minimap->setPosition({
      background_position.x + _margin, 2 * _size.y / 3 });

  graphics::Size2 minimap_frame_size { _size.x - _margin * 2, _size.y / 4 };
  _minimap->setFrameSize(minimap_frame_size);

  // Set the grid offset (map rendering zone size: 1/2 left room)
  using namespace graphics;
  using p = graphics::Properties;
  auto size = static_cast<component> (GraphicsEngine::windowSize().x) - _margin;
  auto nb_col = static_cast<component> (_map->nbColumns());
  p::setGridOffsetX((draw_offset + size - p::cellWidth() * nb_col) / 2);
}



void Panel::update()
{
  _background->setSize(_size);

  auto edge_len = std::min(_size.x / 3, _size.y / 3);

  // Terrain
  _frameCell->setSize({ edge_len, edge_len });
  _terrainDataPos = {
    _frameCell->position().x + _frameUnit->size().x + _margin,
    _frameCell->position().y + _margin
  };

  // Unit
  _frameUnit->setSize({ edge_len, edge_len });
  _frameUnit->setPosition(
    _frameCell->position().x,
    _frameCell->position().y + _frameCell->size().x + 4 * _margin);
  _unitDataPos = {
    _frameUnit->position().x + _frameUnit->size().x + _margin,
    _frameUnit->position().y + _margin
  };

  // Meta information
  _metaInfoPos = {
    _background->position().x + _margin,
    _background->position().y + _size.y - _margin
      - static_cast<float> (_fontSize)
  };

  // MiniMap
  _minimap->update();
}



void Panel::draw()
{
  if (_status == e_panel_status::DEACTIVATED)
  {
    return;
  }

  update();
  _background->draw();

  // Frames
  drawTerrainFrame();
  drawUnitFrame();

  // Meta information
  drawMetaInfo();

  // MiniMap
  _minimap->draw();
}



void Panel::drawTerrainFrame()
{
  // Map Cell under the Cursor
  const auto cell(_map->cell(_playerCursor->coords()));

  _frameCell->draw();

  const auto& terrain = TerrainsHandler::get(cell->terrain());
  graphics::Sprite img(terrain.texture());
  img.setPosition(_frameCell->position().x + _margin,
                  _frameCell->position().y + _margin);

  auto sz(_frameCell->size());
  sz.x -= 10;
  sz.y -= 10;
  img.setSize(sz);
  img.draw();

  // Terrain data text
  const auto& terrain_data =
    terrain.name() + '\n' +
    "cover: " + std::to_string(terrain.cover());

  drawDataText(terrain_data, _terrainDataPos);
}



void Panel::drawUnitFrame()
{
  // Map Cell under the Cursor
  const auto unit{_map->cell(_playerCursor->coords())->unit()};
  if (!unit)
  {
    return; // Draw nothing if no Unit is under the Cursor
  }

  // Unit sprite
  _frameUnit->draw();
  auto sprite(unit->sprite());
  sprite->setPosition(_frameUnit->position().x + _margin,
                      _frameUnit->position().y + _margin);

  auto size{_frameUnit->size()};
  size.x -= 10;
  size.y -= 10;
  sprite->setSize(size);
  sprite->draw();

  // Unit data text
  const auto& unit_data =
    "hp:     " + std::to_string(unit->hp())          + '\n' +
    "motion: " + std::to_string(unit->motionValue()) + '\n' +
    "attack: " + std::to_string(unit->attackValue());

  drawDataText(unit_data, _unitDataPos);

  // Crew
  if (unit->canHaveCrew())
  {
    drawCrew();
  }

  drawEquippedItems();
}



void Panel::drawCrew()
{
  const auto unit{_map->cell(_playerCursor->coords())->unit()};
  auto sprite(unit->sprite());
  graphics::Pos2 crew_pos = {
    _frameUnit->position().x,
    _frameUnit->position().y + sprite->size().y + 2 * _margin
  };

  if (unit->crewSize() <= 0)
  {
    drawDataText("No Crew", crew_pos);
    return;
  }

  auto size{_frameUnit->size()};

  // Compute crew member frame size
  const graphics::Size2 crew_member_size({
    size.x = (size.x - 2 * _margin) / 2,
    size.y = (size.y - 2 * _margin) / 2
  });

  drawDataText("Role",
               { crew_pos.x + crew_member_size.y + 2 * _margin, crew_pos.y },
               16);
  drawDataText("HP     Attack",
               { _background->position().x + _size.x / 2, crew_pos.y },
               16);


  const auto vehicle = std::static_pointer_cast<Vehicle> (unit);

  // First crew member frame position
  crew_pos.y += sprite->size().y + _margin * 2;

  float i = 0.f; // loop iterations in order to compute the offset position

  for (const auto& mbr: vehicle->crew())
  {
    auto mbr_sprite(mbr.second->sprite());
    mbr_sprite->setPosition(_frameUnit->position().x + _margin,
                            _frameUnit->position().y + _frameUnit->size().y
                              + 2 * _margin + i * crew_member_size.y);

    mbr_sprite->setSize(crew_member_size);
    mbr_sprite->draw();

    // Unit data text
    const auto& role{UNIT_ROLE_STR.at(mbr.first)};
    drawDataText(role,
                { mbr_sprite->position().x + _margin + crew_member_size.x,
                  mbr_sprite->position().y + crew_member_size.y / 2 },
                14);

    const auto& crew_data{  std::to_string(mbr.second->hp()) + "          "
                          + std::to_string(mbr.second->attackValue())};
    drawDataText(crew_data,
                { _background->position().x + _size.x / 2,
                  mbr_sprite->position().y + crew_member_size.y / 2 },
                14);

    ++i;
  }
}



void Panel::drawEquippedItems()
{
  const auto unit{_map->cell(_playerCursor->coords())->unit()};
  if (!unit)
  {
    return; // Draw nothing if no Unit is under the Cursor
  }

  const auto offset_y =
      _frameUnit->position().y + unit->sprite()->size().y + 8 * _margin
    + static_cast<float> (unit->crewSize()) * _frameUnit->size().y;

  unit->inventory()->drawInPanel(
    { _background->position().x + _margin, offset_y });
}



void Panel::drawDataText(const std::string& data, const graphics::Pos2& pos)
{
  drawDataText(data, pos, _fontSize);
}



void Panel::drawDataText(const std::string& data,
                         const graphics::Pos2& pos,
                         size_t size)
{
  auto text = std::make_unique<resources::Text> (data, size, pos);
  text->draw();
}



void Panel::drawMetaInfo()
{
  using namespace graphics;

  // Draw the FPS
  std::stringstream fpsStream;
  fpsStream << "fps: " << static_cast<int> (tools::Fps::getFps() + 0.5);

  resources::Text fpsText(fpsStream.str(), _fontSize, _metaInfoPos);
  fpsText.draw();


  // Draw the time
  auto now = std::time(nullptr);
  auto time = std::localtime(&now);
  char buffer[6];
  std::strftime(buffer, 6, "%H:%M", time);

  auto dateText = std::make_unique<resources::Text> (buffer, _fontSize);
  if (_dateWidth < 0.1f)
  {
    _dateWidth = dateText->getSize().x;
  }

  auto text_pos = _metaInfoPos + Pos2{ _size.x - 2 * _margin - _dateWidth, 0 };
  dateText->setPosition(text_pos);
  dateText->draw();
}


} // namespace interface
