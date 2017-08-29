/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class definition
 */


#include <interface/Panel.hh>
#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>
#include <debug/Debug.hh>


namespace interface {

Panel::Panel()
  : InterfaceElement("side_panel")
  , _background(resources::ResourcesManager::getImage(_img_name))
  , _status(e_panel_status::DEACTIVATED)
{
  setWindowSize(
      {static_cast<float> (graphics::GraphicsEngine::windowSize().x),
       static_cast<float> (graphics::GraphicsEngine::windowSize().y)}
    );
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

  if (_status == e_panel_status::POSITION_RIGHT)
  {
    _background->setPosition(3 * _windowSize.x / 4.f, 0);
  }
  else
  {
    _background->setPosition(0, 0);
  }

  _background->setSize(_size);
}


void Panel::update()
{
  _background->setSize(_size);
}


void Panel::draw()
{
  if (_status == e_panel_status::DEACTIVATED)
  {
    return;
  }

  update();
  _background->draw();
}


} // namespace interface
