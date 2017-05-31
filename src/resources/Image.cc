#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <debug/Debug.hh>
#include <cassert>

namespace resources {


Image::Image(const std::string file_name, const std::string name)
{
   /// \todo allocation only if needed (using a proxy)
  _rectangle = std::make_shared<graphics::RectangleShape> ();
  _rectangle->setPosition(graphics::Pos2(0, 0));
  _rectangle->setSize(graphics::Size2(0, 0));

   /// \todo in debug, load an ugly texture to help noticing it
# ifdef DEBUG
  _rectangle->setTexture(nullptr);
# else
  _rectangle->setTexture(nullptr);
# endif

  _fileName = file_name;
  _name = name;
  _loaded = false;
  //_scope = E_SCOPE_ALL;
}


std::shared_ptr<graphics::Texture> Image::getTexture()
{
  if (!_texture)
  {
    _texture = std::make_shared<graphics::Texture> ();
    _texture->loadFromFile(_fileName);
    _rectangle->setTexture(_texture.get());
    _loaded = true;
  }

  return _texture;
}


void Image::initTexture()
{
# ifdef DEBUG
  if (_fileName == "")
  {
    Debug::logPrintf(__FILE__, " at line ", __LINE__,
                     "Unable to initialize a texture without fileName");
  }
# endif // DEBUG

  assert(_fileName != "");

  _texture = std::make_shared<graphics::Texture> ();
  _texture->loadFromFile(_fileName);
  _rectangle->setTexture(_texture.get());
  _loaded = true;
}


void Image::initSprite()
{
  if (!_texture)
  {
    _texture = std::make_shared<graphics::Texture> ();
    _texture->loadFromFile(_fileName);
    _rectangle->setTexture(_texture.get());
    _loaded = true;
  }

  _sprite = std::make_shared<graphics::Sprite> (*_texture);
  _loaded = true;
}


std::shared_ptr<graphics::Sprite> Image::sprite()
{
  if (!_texture)
    initTexture();

  if (!_sprite)
    initSprite();

  return _sprite;
}


void Image::setFileName(const std::string file_name)
{
  _fileName = file_name;
  _loaded = false;
}


void Image::setPosition(const Coords position)
{
  if (!_sprite) {
    initSprite();
  }

  _sprite->setPosition({static_cast<graphics::component> (position.c),
                        static_cast<graphics::component> (position.l)});
}


void Image::setPosition(const graphics::component x, const graphics::component y)
{
  if (!_sprite) {
    initSprite();
  }
  _sprite->setPosition({x, y});
}


void Image::setSize(const graphics::Size2 size)
{
  auto old_size(_rectangle->getSize());
  _rectangle->setSize(size);
  _sprite->setScale({size.x / old_size.x, size.y / old_size.y});
}


void Image::setSize(const graphics::component width,
                    const graphics::component height)
{
  graphics::Size2 size(_texture->getSize()); // explicit Vector2f for -Wconversion
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


bool Image::load()
{
  if (_loaded) {
  	return true;
  }

  if (!_texture) {
    _texture = std::make_shared<graphics::Texture> ();
  }

  _rectangle->setTexture(_texture.get(), true);

  _texture->loadFromFile(_fileName);
  _loaded = true;

  return false;
}


void Image::unload()
{
  if (!_texture) {
    return;
  }

  //delete _texture; // reset() ?
  _loaded = false;

# ifdef DEBUG
  _rectangle->setTexture(nullptr);
# endif
}


void Image::reload(const std::string file_name)
{
  // if (_texture)
  //   delete _texture;

  _texture->loadFromFile(file_name);
  _rectangle->setTexture(_texture.get());
  _loaded = true;
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

  if (load()) {
    GraphicsEngine::draw(_sprite);
  }

  GraphicsEngine::draw(_rectangle);
}


void Image::draw()
{
  if (!_sprite) {
    sprite();
  }

  _rectangle->setPosition(_sprite->getPosition());

  if (load()) {
    graphics::GraphicsEngine::draw(_sprite);
  }

  graphics::GraphicsEngine::draw(_rectangle);
}


} // namespace resources
