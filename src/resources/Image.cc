#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <debug/Debug.hh>


namespace resources {


Image::Image(const std::string file_name, const std::string name)
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


void Image::setPosition(const Coords position)
{
  _sprite->setPosition({static_cast<graphics::component> (position.c),
                        static_cast<graphics::component> (position.l)});
}


void Image::setPosition(const graphics::component x, const graphics::component y)
{
  _sprite->setPosition({x, y});
}


void Image::setSize(const graphics::Size2 size)
{
  graphics::Size2 texture_size(_texture->getSize());
  _rectangle->setSize({size.x / texture_size.x, size.y / texture_size.y});
  _sprite->setScale({size.x / texture_size.x, size.y / texture_size.y});
}


void Image::setSize(const graphics::component width,
                    const graphics::component height)
{
  graphics::Size2 size(_texture->getSize());
  _rectangle->setSize({width / size.x, height / size.y});
  _sprite->setScale({width / size.x, height / size.y});
}


void Image::setScale(const graphics::Scale2 scale)
{
  _rectangle->setScale(scale);
  _sprite->setScale(scale);
}


void Image::setScale(const float width, const float height)
{
  _rectangle->setScale({width, height});
  _sprite->setScale({width, height});
}


void Image::setScale(const float ratio)
{
  _rectangle->setScale({ratio, ratio});
  _sprite->setScale({ratio, ratio});
}


void Image::drawAtCell(const Coords c)
{
  if (!_sprite) {
    sprite();
  }

  // Set the sprite position
  using namespace graphics;
  using p = MapGraphicsProperties;
  _sprite->setPosition(
    {static_cast<component> (c.c) * p::cellWidth()  + p::gridOffsetX(),
     static_cast<component> (c.l) * p::cellHeight() + p::gridOffsetY()});

  GraphicsEngine::draw(_sprite);
}


void Image::draw()
{
  if (!_sprite) {
    sprite();
  }

  _rectangle->setPosition(_sprite->getPosition());

  graphics::GraphicsEngine::draw(_sprite);
}


} // namespace resources
