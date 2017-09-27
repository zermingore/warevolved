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
#include <resources/Sprite.hh>
#include <graphics/GraphicsEngine.hh>
#include <common/enums/terrains.hh>



namespace interface {


/// \todo make frame_cell, frame_unit and frame minimap textures
Panel::Panel(std::shared_ptr<const Map> map,
             std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("side_panel")
  , _map(map)
  , _playerCursor(cursor)
  , _background(resources::ResourcesManager::getSprite(_img_name))
  , _frameCell(resources::ResourcesManager::getSprite("frame_thumbnail"))
  , _frameUnit(resources::ResourcesManager::getSprite("frame_thumbnail"))
  , _status(e_panel_status::DEACTIVATED)
{
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

  Coords background_position {0, 0};
  if (_status == e_panel_status::POSITION_RIGHT)
  {
    background_position = { static_cast<size_t> (3 * _windowSize.x / 4.f), 0 };
  }
  else
  {
    background_position = { 0, 0 };
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
}



void Panel::update()
{
  _background->setSize(_size);
  _frameCell->setSize({ _size.x, _size.y / 4 });
  _frameUnit->setSize({ _size.x, _size.y / 4 });
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
      auto img(resources::ResourcesManager::getSprite("forest"));
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


  // Unit
  const auto unit(cell->unit());
  if (unit)
  {
    _frameUnit->draw();
    auto img(unit->image());
    img->setPosition(_frameUnit->position().x + 5,
                     _frameUnit->position().y + 5);

    auto size(_frameUnit->size());
    size.x -= 10;
    size.y -= 10;
    img->setSize(size);

    img->draw();
  }


  // MiniMap
  _minimap->draw();
}


} // namespace interface
