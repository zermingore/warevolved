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
  _windowSize = size;

  _size.x = _windowSize.x / 4;
  _size.y = _windowSize.y;
  _background->setSize(_size);
}



void Panel::toggleStatus()
{
  _status = static_cast<e_panel_status> (
    (static_cast<int> (_status) + 1)
    % static_cast<int> (e_panel_status::NB_PANEL_STATUS));

  // Coords background_position { 0, 0 };
  graphics::Pos2 background_position;
  auto draw_offset(0.f); // rendering room offset
  switch (_status)
  {
    case e_panel_status::POSITION_LEFT:
      draw_offset = _windowSize.x / 4.f;
      break;

    case e_panel_status::POSITION_RIGHT:
      draw_offset = -_windowSize.x / 4.f;
      background_position.x = 3.f * _windowSize.x / 4.f;
      break;

    default:
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
      background_position.x + _margin, 2 * _windowSize.y / 3 });


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
    _background->position().x + _size.x - _margin - _dateWidth,
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
  auto image();
  switch (terrain)
  {
    case e_terrain::FOREST:
    {
      auto img(std::make_unique<graphics::Sprite> ("forest"));
      /// \todo Do not hard-code the offset (frame thickness) + adapt scale
      img->setPosition(_frameCell->position().x + _margin,
                       _frameCell->position().y + _margin);

      auto size(_frameCell->size());
      size.x -= 10;
      size.y -= 10;
      img->setSize(size);
      img->draw();
      break;
    }

    default:
      // Not using the enum printer here as the terrains will be a class
      ERROR("Terrain is invalid", static_cast<int> (cell->terrain()));
      break;
  }


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
    addUnitData("hp:     " + std::to_string(unit->hp()));
    addUnitData("motion: " + std::to_string(unit->motionValue()));
    addUnitData("attack: " + std::to_string(unit->attackValue()));

    drawUnitData();
  }

  // Meta information
  drawMetaInfo();

  // MiniMap
  _minimap->draw();
}



void Panel::addUnitData(const std::string content)
{
  _unitDataText += content + '\n';
}



void Panel::drawUnitData()
{
  auto text = std::make_unique<resources::Text> (
    _unitDataText, _fontSize, _unitDataPos);

  _unitDataText.clear();
  graphics::GraphicsEngine::draw(text->graphicalText());
}



void Panel::drawMetaInfo()
{
  auto now = std::time(nullptr);
  auto time = std::localtime(&now);
  char buffer[6];
  std::strftime(buffer, 6, "%H:%M", time);

  auto dateText = std::make_unique<resources::Text> (
    buffer, _fontSize, _metaInfoPos);

  if (_dateWidth < 0.1f)
    _dateWidth = dateText->graphicalText()->getLocalBounds().width;

  graphics::GraphicsEngine::draw(dateText->graphicalText());
}


} // namespace interface
