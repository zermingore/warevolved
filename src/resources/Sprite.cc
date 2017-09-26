#include <resources/Sprite.hh>

#include <graphics/graphic_types.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <debug/Debug.hh>



namespace resources {


Sprite::Sprite(const std::string file_name, const std::string name)
{
  _name = name;
  _fileName = file_name;

  _rectangle = std::make_shared<graphics::RectangleShape> ();
  _rectangle->setPosition(graphics::Pos2(0, 0));
  _rectangle->setSize(graphics::Size2(0, 0));

  _texture = std::make_shared<graphics::Texture> ();
  _texture->loadFromFile(_fileName);
  _rectangle->setTexture(_texture.get());

  _sprite = std::make_shared<graphics::Sprite> (*_texture);
}



Sprite::Sprite(const std::shared_ptr<graphics::Texture> texture,
               const std::string name)
{
  _name = name;
  _fileName = "texture init";

  _rectangle = std::make_shared<graphics::RectangleShape> ();
  _rectangle->setPosition(graphics::Pos2(0, 0));
  _rectangle->setSize(graphics::Size2(0, 0));

  _texture = texture;
  _rectangle->setTexture(_texture.get());

  _sprite = std::make_shared<graphics::Sprite> (*_texture);
}



graphics::Pos2 Sprite::position()
{
  return _sprite->getPosition();
}


void Sprite::setPosition(size_t x, size_t y)
{
  _sprite->setPosition({ static_cast<graphics::component> (x),
                         static_cast<graphics::component> (y) });
}

void Sprite::setPosition(const Coords position)
{
  _sprite->setPosition({ static_cast<graphics::component> (position.c),
                         static_cast<graphics::component> (position.l) });
}

void Sprite::setPosition(const graphics::component c, const graphics::component l)
{
  _sprite->setPosition({ c, l });
}

void Sprite::setPosition(const graphics::Pos2 position)
{
  _sprite->setPosition({ position.x, position.y });
}


graphics::Size2 Sprite::size()
{
  return _rectangle->getSize();
}


void Sprite::setSize(const graphics::Size2 size)
{
  graphics::Size2 texture_size(_texture->getSize());
  _rectangle->setSize({ size.x, size.y });
  _sprite->setScale({ size.x / texture_size.x, size.y / texture_size.y });
}


void Sprite::setSize(const graphics::component width,
                     const graphics::component height)
{
  graphics::Size2 size(_texture->getSize());
  _rectangle->setSize({ width, height });
  _sprite->setScale({ width / size.x, height / size.y });
}


void Sprite::setScale(const graphics::Scale2 scale)
{
  _rectangle->setScale(scale);
  _sprite->setScale(scale);
}


void Sprite::setScale(const float width, const float height)
{
  _rectangle->setScale({width, height});
  _sprite->setScale({width, height});
}


void Sprite::setScale(const float ratio)
{
  _rectangle->setScale({ratio, ratio});
  _sprite->setScale({ratio, ratio});
}


void Sprite::setColor(const graphics::Color& color)
{
  _sprite->setColor(color);
}



void Sprite::drawAtCell(const Coords c)
{
  // Set the sprite position
  using namespace graphics;
  using p = MapGraphicsProperties;
  _sprite->setPosition(
    { static_cast<component> (c.c) * p::cellWidth()  + p::gridOffsetX(),
      static_cast<component> (c.l) * p::cellHeight() + p::gridOffsetY() });

  GraphicsEngine::draw(_sprite);
}


void Sprite::draw()
{
  _rectangle->setPosition(_sprite->getPosition());
  graphics::GraphicsEngine::draw(_sprite);
}


} // namespace resources
