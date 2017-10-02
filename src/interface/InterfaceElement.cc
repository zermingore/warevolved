/**
 * \file
 * \date Jan 11, 2015
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#include <interface/InterfaceElement.hh>
#include <resources/ResourcesManager.hh>
#include <graphics/Sprite.hh>


namespace interface {


InterfaceElement::InterfaceElement(const std::string &image_name)
  : _imgName(image_name)
{
  _sprite = std::make_shared<graphics::Sprite> (_imgName);
  _scale.x = static_cast<float> (_sprite->texture()->getSize().x);
  _scale.y = static_cast<float> (_sprite->texture()->getSize().y);
}


} // namespace interface
