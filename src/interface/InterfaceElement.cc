/**
 * \file
 * \namespace interface
 * \brief InterfaceElements implementation
 */

#include <interface/InterfaceElement.hh>

namespace interface {


InterfaceElement::InterfaceElement(const std::string &image_name) :
  _img_name(image_name)
{

  //  float x(image.sprite()->getTexture()->getSize().x);
  //  float y(image.sprite()->getTexture()->getSize().y);
  //  image.sprite()->setScale(p->cellWidth() / x, p->cellHeight() / y);
}

} // namespace interface
