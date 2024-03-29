/**
 * \file
 * \date Apr 25, 2013
 * \author Zermingore
 * \namespace graphics
 * \brief Sprite class definition
 */

#include <graphics/Sprite.hh>

#include <debug/Debug.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Properties.hh>
#include <graphics/graphic_types.hh>
#include <resources/ResourcesManager.hh>



namespace graphics {


Sprite::Sprite(const std::string& file_name)
  : _texture(resources::ResourcesManager::getTexture(file_name))
  , _sprite(std::make_shared<sf::Sprite> (*_texture))
  , _rectangle(std::make_shared<RectangleShape> ())
{
  _rectangle->setPosition({0, 0});
  _rectangle->setSize({0, 0});
  _rectangle->setTexture(_texture.get());
}



Sprite::Sprite(const std::shared_ptr<Texture>& texture)
  : _texture(texture)
  , _sprite(std::make_shared<sf::Sprite> (*_texture))
  , _rectangle(std::make_shared<RectangleShape> ())
{
  _rectangle->setPosition(0, 0);
  _rectangle->setSize({0, 0});
  _rectangle->setTexture(_texture.get());
}



void Sprite::setTexture(const std::string& file_name)
{
  _rectangle = std::make_shared<RectangleShape> ();
  _rectangle->setPosition({0, 0});
  _rectangle->setSize({0, 0});

  _texture = resources::ResourcesManager::getTexture(file_name);
  _rectangle->setTexture(_texture.get());

  _sprite = std::make_shared<sf::Sprite> (*_texture);
}



void Sprite::setTexture(const Texture& texture)
{
  _rectangle = std::make_shared<RectangleShape> ();
  _rectangle->setPosition({0, 0});
  _rectangle->setSize({0, 0});

  _texture = std::make_shared<graphics::Texture> (texture);
  _rectangle->setTexture(_texture.get());

  _sprite = std::make_shared<sf::Sprite> (*_texture);
}



void Sprite::setTextureRepeat(bool repetition)
{
  _texture->setRepeated(repetition);

  _sprite = std::make_shared<sf::Sprite> (*_texture);
  _sprite->setTextureRect({
    0,
    0,
    static_cast<int> (_rectangle->getSize().x),
    static_cast<int> (_rectangle->getSize().y)
  });
  _rectangle->setTexture(_texture.get());
}



Pos2 const Sprite::position()
{
  return Pos2{_sprite->getPosition()};
}



void Sprite::setPosition(const Coords position)
{
  _sprite->setPosition({ static_cast<component> (position.c),
                         static_cast<component> (position.l) });
}



void Sprite::setPosition(const Pos2 position)
{
  _sprite->setPosition({ position.x, position.y });
}



Size2 const Sprite::size()
{
  return Size2{_rectangle->getSize()};
}



void Sprite::setSize(const Size2 size)
{
  _rectangle->setSize({ size.x, size.y });
  _sprite->setScale(size / Size2{_texture->getSize()});
}



void Sprite::setOrigin(float x, float y)
{
  _sprite->setOrigin(x, y);
}



void Sprite::setRotation(float angle)
{
  _sprite->setRotation(angle);
}



void Sprite::setScale(const Scale2 scale)
{
  _rectangle->setScale(scale.x, scale.y);
  _sprite->setScale(scale.x, scale.y);
}



void Sprite::setScale(float ratio)
{
  _rectangle->setScale({ ratio, ratio });
  _sprite->setScale({ ratio, ratio });
}



void Sprite::setColor(const Color& color)
{
  _sprite->setColor(color);
}



void Sprite::drawAtCell(const Coords c)
{
  // Set the sprite position
  using namespace graphics;
  using p = graphics::Properties;
  _sprite->setPosition(
    { static_cast<component> (c.c) * p::cellWidth()  + p::gridOffsetX(),
      static_cast<component> (c.l) * p::cellHeight() + p::gridOffsetY() });

  GraphicsEngine::draw(_sprite);
}



void Sprite::draw()
{
  _rectangle->setPosition(_sprite->getPosition());
  GraphicsEngine::draw(_sprite);
}


} // namespace graphics
