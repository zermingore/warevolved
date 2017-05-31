/**
 * \file
 * \date Jan 11, 2015
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#include <interface/InterfaceElement.hh>
#include <resources/Image.hh>
#include <resources/ResourcesManager.hh>
#include <graphics/graphics.hh>


namespace interface {


InterfaceElement::InterfaceElement(const std::string &image_name)
  : _img_name(image_name)
  , _image(resources::ResourcesManager::getImage(_img_name))
{
  _scale.x = static_cast<float> (_image->sprite()->getTexture()->getSize().x);
  _scale.y = static_cast<float> (_image->sprite()->getTexture()->getSize().y);
}


} // namespace interface
