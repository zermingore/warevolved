/**
 * \file
 * \namespace interface
 * \brief InterfaceElement implementation
 */

#include <interface/InterfaceElement.hh>
#include <resources/Image.hh>
#include <resources/ResourcesManager.hh>
#include <graphics/GraphicsEngine.hh>


namespace interface {


InterfaceElement::InterfaceElement(const std::string &image_name)
  : _img_name(image_name)
  , _image(resources::ResourcesManager::getImage(_img_name))
{
  _scale.x = _image.sprite()->getTexture()->getSize().x;
  _scale.y = _image.sprite()->getTexture()->getSize().y;

//  _image.sprite()->setScale(p->cellWidth() / _scale.x, p->cellHeight() / _scale.y);
}


std::shared_ptr<sf::Sprite> InterfaceElement::getSprite()
{
  auto sprite(_image.sprite());
  sprite->setRotation(_rotation);
  sprite->setPosition(sf::Vector2f(_position.x, _position.y));

  return sprite;
}


void InterfaceElement::draw()
{
  PRINTF("interfaceelement::draw()", _img_name);
  graphics::GraphicsEngine::draw(_image.sprite());
}



} // namespace interface
