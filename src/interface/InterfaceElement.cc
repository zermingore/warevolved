/**
 * \file
 * \date Jan 11, 2015
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#include <graphics/Sprite.hh>
#include <interface/InterfaceElement.hh>
#include <resources/ResourcesManager.hh>
#include <utility>


namespace interface {


InterfaceElement::InterfaceElement(const std::string& image_name)
  : _imgName(image_name)
{
  _sprite = std::make_shared<graphics::Sprite> (_imgName);
  _scale.x = static_cast<float> (_sprite->texture()->getSize().x);
  _scale.y = static_cast<float> (_sprite->texture()->getSize().y);
}


} // namespace interface
