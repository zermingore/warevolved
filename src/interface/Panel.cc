/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class definition
 */


#include <interface/Panel.hh>

#include <algorithm> // std:min

#include <debug/Debug.hh>
#include <tools/Fps.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <common/enums/terrains.hh>
#include <interface/Cursor.hh>
#include <interface/MiniMap.hh>
#include <resources/Text.hh>
#include <graphics/graphic_types.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>



namespace interface {


Panel::Panel(std::shared_ptr<const Map> map,
             std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("side_panel")
  , _map(map)
  , _playerCursor(cursor)
  , _status(e_panel_status::DEACTIVATED)
  , _fontSize(20)
  , _dateWidth(0)
{
  _background = std::make_unique<graphics::Sprite> (_imgName);
  _frameCell = std::make_unique<graphics::Sprite> ("frame_thumbnail");
  _frameUnit = std::make_unique<graphics::Sprite> ("frame_thumbnail");

  setWindowSize(graphics::GraphicsEngine::windowSize());
  graphics::Size2 size { _size.x - _margin * 2, _size.y / 4 };
  _minimap = std::make_unique<MiniMap> (size, map, cursor);
}



void Panel::setWindowSize(const graphics::Size2& size)
{
  _size.x = size.x / 4;
  _size.y = size.y;
  _background->setSize(_size);
}



void Panel::toggleStatus()
{
  _status = static_cast<e_panel_status> (
    (static_cast<int> (_status) + 1)
    % static_cast<int> (e_panel_status::NB_PANEL_STATUS));

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
      break;
  }

  _background->setPosition(background_position);
  _background->setSize(_size);


  // Terrain
  _frameCell->setPosition(background_position.x + _margin, _margin);

  // Unit
  _frameUnit->setPosition(background_position.x + _margin, _size.y / 3);

  // MiniMap
  _minimap->setPosition({
      background_position.x + _margin, 2 * _size.y / 3 });


  // Set the grid offset (map rendering zone size: 1/2 left room)
  using namespace graphics;
  using p = MapGraphicsProperties;
  auto size = static_cast<component> (GraphicsEngine::windowSize().x) - _margin;
  auto nb_col = static_cast<component> (_map->nbColumns());
  p::setGridOffsetX((draw_offset + size - p::cellWidth() * nb_col) / 2);
}



void Panel::update()
{
  _background->setSize(_size);

  auto edge_len = std::min(_size.x / 2, _size.y / 4);

  // Terrain
  _frameCell->setSize({ edge_len, edge_len });

  // Unit
  _frameUnit->setSize({ edge_len, edge_len });
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
  if (_status == e_panel_status::DEACTIVATED) {
    return;
  }

  update();
  _background->draw();

  // Map Cell under the Cursor
  const auto cell(_map->cell(_playerCursor->coords()));

  // Terrain
  _frameCell->draw();
  const auto terrain(cell->terrain());
  graphics::Sprite img(TerrainsHandler::get(terrain).name());
  img.setPosition(_frameCell->position().x + _margin,
                  _frameCell->position().y + _margin);

  auto sz(_frameCell->size());
  sz.x -= 10;
  sz.y -= 10;
  img.setSize(sz);
  img.draw();


  // Unit frame
  const auto unit(cell->unit());
  if (unit)
  {
    // Unit sprite
    _frameUnit->draw();
    auto sprite(unit->sprite());
    sprite->setPosition(_frameUnit->position().x + _margin,
                        _frameUnit->position().y + _margin);

    auto size(_frameUnit->size());
    size.x -= 10;
    size.y -= 10;
    sprite->setSize(size);

    sprite->draw();

    // Unit data
    const auto& unit_data =
      "hp:     " + std::to_string(unit->hp())          + '\n' +
      "motion: " + std::to_string(unit->motionValue()) + '\n' +
      "attack: " + std::to_string(unit->attackValue());

    drawDataText(unit_data, _unitDataPos);
  }

  // Meta information
  drawMetaInfo();

  // MiniMap
  _minimap->draw();
}



void Panel::drawDataText(const std::string& data, const graphics::Pos2& pos)
{
  auto text = std::make_unique<resources::Text> (data, _fontSize, pos);
  text->draw();
}



void Panel::drawMetaInfo()
{
  using namespace graphics;

  // Draw the FPS /// \todo On release, display max(60, fps)
  std::stringstream fpsStream;
  fpsStream << "fps: " << static_cast<int> (tools::Fps::getFps() + 0.5);

  auto fpsText = std::make_unique<resources::Text> (
    fpsStream.str(), _fontSize, _metaInfoPos);

  fpsText->draw();


  // Draw the time
  auto now = std::time(nullptr);
  auto time = std::localtime(&now);
  char buffer[6];
  std::strftime(buffer, 6, "%H:%M", time);

  auto dateText = std::make_unique<resources::Text> (buffer, _fontSize);
  if (_dateWidth < 0.1f)
    _dateWidth = dateText->getSize().x;

  auto text_pos = _metaInfoPos + Pos2{ _size.x - 2 * _margin - _dateWidth, 0 };
  dateText->setPosition(text_pos);

  dateText->draw();
}


} // namespace interface
