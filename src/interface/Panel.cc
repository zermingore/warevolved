/**
 * \file
 * \date August 22, 2017
 * \author Zermingore
 * \brief Side panel class definition
 */


#include <interface/Panel.hh>
#include <resources/Image.hh>

namespace interface {

Panel::Panel()
  : InterfaceElement("side_panel")
  , _background(resources::ResourcesManager::getImage(_img_name))
{
  _background->setSize(0, 0);
}


void Panel::update()
{
  _background->setPosition(_position.x, _position.y);
}


void Panel::draw()
{
  update();
  _background->draw();
}



} // namespace interface
