/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class definition
 */


#include <interface/Panel.hh>
#include <interface/Cursor.hh>
#include <interface/MiniMap.hh>
#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>
#include <debug/Debug.hh>

# include <game/Map.hh>
# include <interface/Cursor.hh>


namespace interface {

Panel::Panel(std::shared_ptr<const Map> map,
             std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("side_panel")
  , _playerCursor(cursor)
  , _background(resources::ResourcesManager::getImage(_img_name))
  , _frameCell(resources::ResourcesManager::getImage("frame_cell"))
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


Panel::~Panel()
{
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
}



void Panel::update()
{
  _background->setSize(_size);
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
}


} // namespace interface
