/**
 * \file
 * \namespace interface
 * \brief InterfaceElements implementation
 */

#include <interface/InterfaceElement.hh>
#include <resources/Image.hh>
#include <resources/ResourcesManager.hh>

namespace interface {


InterfaceElement::InterfaceElement(const std::string &image_name) :
  _img_name(image_name)
{

  //  float x(image.sprite()->getTexture()->getSize().x);
  //  float y(image.sprite()->getTexture()->getSize().y);
  //  image.sprite()->setScale(p->cellWidth() / x, p->cellHeight() / y);
}


std::shared_ptr<sf::Sprite> InterfaceElement::getSprite()
{
  graphics::Image& image(resources::ResourcesManager::getImage(_img_name));

  auto sprite(image.sprite());
  sprite->setRotation(_rotation);
  sprite->setPosition(sf::Vector2f (_position.x, _position.y));

  return sprite;
}


} // namespace interface
