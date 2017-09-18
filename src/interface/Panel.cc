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
  , _background(resources::ResourcesManager::getImage(_img_name))
  , _frameCell(resources::ResourcesManager::getImage("cursor"))
  , _frameUnit(resources::ResourcesManager::getImage("frame_unit"))
  , _status(e_panel_status::DEACTIVATED)
{
  setWindowSize(
      {static_cast<float> (graphics::GraphicsEngine::windowSize().x),
       static_cast<float> (graphics::GraphicsEngine::windowSize().y)}
    );

  std::pair<size_t, size_t> size {_size.x, _size.y / 4};
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
    background_position = {static_cast<size_t> (3 * _windowSize.x / 4.f), 0};
  }
  else
  {
    background_position = {0, 0};
  }
  _background->setPosition(background_position);
  _background->setSize(_size);

  _minimap->setPosition({background_position.x,
                         static_cast<size_t> (_windowSize.y / 2)});

  _frameCell->setPosition({background_position.x, 0});
  _frameCell->setSize(_size);
}



void Panel::update()
{
  _background->setSize(_size);
  _frameCell->setSize({ _size.x, _size.y / 4 });

  const auto cell(_map->cell(_playerCursor->coords()));

  const auto terrain(cell->terrain());
  auto image();
  switch (terrain)
  {
    case e_terrain::FOREST:
    {
      auto img(resources::ResourcesManager::getImage("forest"));
      img->setPosition(0, 0);
      img->draw();
      break;
    }

    default:
      // Not using the enum printer here as the terrains will be a class
      ERROR("Terrain is invalid", static_cast<int> (cell->terrain()));
      break;
  }

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
  _minimap->draw();
  _frameCell->draw();
}


} // namespace interface
