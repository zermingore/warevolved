/**
 * \file
 * \date Jan 11, 2015
 * \author Zermingore
 * \namespace interface
 * \brief InterfaceElement class implementation
 */

#include <graphics/Sprite.hh>
#include <interface/InterfaceElement.hh>
#include <resources/ResourcesManager.hh>
#include <utility>


namespace interface {


InterfaceElement::InterfaceElement(const std::string& image_name)
  : _imgName(image_name)
  , _sprite(std::make_shared<graphics::Sprite> (_imgName))
  , _position(0.f, 0.f)
{
  _scale.x = static_cast<float> (_sprite->texture()->getSize().x);
  _scale.y = static_cast<float> (_sprite->texture()->getSize().y);
}



void InterfaceElement::setPosition(const graphics::Pos2& position)
{
  _position = position;
  _sprite->setPosition(position);
}



} // namespace interface
