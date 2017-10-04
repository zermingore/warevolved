/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class definition
 */


#include <interface/Panel.hh>

#include <debug/Debug.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <interface/Cursor.hh>
#include <interface/MiniMap.hh>
#include <graphics/Sprite.hh>
#include <resources/Text.hh>
#include <graphics/GraphicsEngine.hh>
#include <common/enums/terrains.hh>
#include <graphics/MapGraphicsProperties.hh>



namespace interface {


/// \todo make frame_cell, frame_unit and frame minimap textures
Panel::Panel(std::shared_ptr<const Map> map,
             std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("side_panel")
  , _map(map)
  , _playerCursor(cursor)
  , _status(e_panel_status::DEACTIVATED)
  , _fontSize(20)
{
  _background = std::make_shared<graphics::Sprite> (_imgName);
  _frameCell = std::make_shared<graphics::Sprite> ("frame_thumbnail");
  _frameUnit = std::make_shared<graphics::Sprite> ("frame_thumbnail");

  setWindowSize(
      {static_cast<float> (graphics::GraphicsEngine::windowSize().x),
       static_cast<float> (graphics::GraphicsEngine::windowSize().y)}
  );

  graphics::Size2 size { _size.x, _size.y / 4 };
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

  Coords background_position { 0, 0 };
  auto draw_offset(0.f); // rendering room offset
  switch (_status)
  {
    case e_panel_status::POSITION_LEFT:
      draw_offset = _windowSize.x / 4.f;
      break;

    case e_panel_status::POSITION_RIGHT:
      draw_offset = -_windowSize.x / 4.f;
      background_position.x = { static_cast<size_t> (3 * _windowSize.x / 4.f) };
      break;

    default:
      break;
  }

  _background->setPosition(background_position);
  _background->setSize(_size);


  // Terrain
  _frameCell->setPosition(background_position.x, 0ul);

  // Unit
  _frameUnit->setPosition(background_position.x,
                          static_cast<size_t> (_size.y / 3));

  // MiniMap
  _minimap->setPosition({ background_position.x,
                          static_cast<size_t> (2 * _windowSize.y / 3) });


  // Set the grid offset (map rendering zone size: 1/2 left room)
  using namespace graphics;
  using p = MapGraphicsProperties;
  auto size = static_cast<component> (GraphicsEngine::windowSize().x);
  auto nb_col = static_cast<component> (_map->nbColumns());
  p::setGridOffsetX((draw_offset + size - p::cellWidth() * nb_col) / 2);
}



void Panel::update()
{
  _background->setSize(_size);

  // Terrain
  _frameCell->setSize({ _size.x, _size.y / 4 });

  // Unit
  _frameUnit->setSize({ _size.x / 2, _size.y / 8 });
  _unitDataPos = { _frameUnit->position().x + _frameUnit->size().x + 5,
                   _frameUnit->position().y + 5 };

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
      auto img(std::make_shared<graphics::Sprite> ("forest"));
      /// \todo Do not hard-code the offset (frame thickness) + adapt scale
      img->setPosition(_frameCell->position().x + 5,
                       _frameCell->position().y + 5);

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
    sprite->setPosition(_frameUnit->position().x + 5,
                        _frameUnit->position().y + 5);

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


  // MiniMap
  _minimap->draw();
}



void Panel::addUnitData(const std::string content)
{
  _unitDataText += content + '\n';
}



void Panel::drawUnitData()
{
  auto text = std::make_shared<resources::Text> (
    _unitDataText, _fontSize, _unitDataPos);

  _unitDataText.clear();
  graphics::GraphicsEngine::draw(text->graphicalText());
}


} // namespace interface
