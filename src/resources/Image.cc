#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>


namespace resources {


Image::Image(const std::string file_name, const std::string name)
{
   /// \todo allocation only if needed (using a proxy)
  _rectangle = std::make_shared<sf::RectangleShape> ();
  _rectangle->setPosition(sf::Vector2f(0, 0));
  _rectangle->setSize(sf::Vector2f(0, 0));

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


std::shared_ptr<sf::Texture> Image::getTexture()
{
  if (!_texture)
  {
    _texture = std::make_shared<sf::Texture> ();
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

  _texture = std::make_shared<sf::Texture> ();
  _texture->loadFromFile(_fileName);
  _rectangle->setTexture((sf::Texture *) (_texture.get()));
  _loaded = true;
}


void Image::initSprite()
{
  if (!_texture)
  {
    _texture = std::make_shared<sf::Texture> ();
    _texture->loadFromFile(_fileName);
    _rectangle->setTexture(_texture.get());
    _loaded = true;
  }

  _sprite = std::make_shared<sf::Sprite> (*_texture);
  _loaded = true;
}


std::shared_ptr<sf::Sprite> Image::sprite()
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
  _sprite->setPosition(sf::Vector2f(position.c, position.l));
}


void Image::setPosition(const size_t x, const size_t y)
{
  if (!_sprite) {
    initSprite();
  }
  _sprite->setPosition(sf::Vector2f(x, y));
}


void Image::setSize(const sf::Vector2f size)
{
  auto old_size(_rectangle->getSize());
  _rectangle->setSize(size);
  _sprite->setScale(sf::Vector2f(size.x / old_size.x, size.y / old_size.y));
}


void Image::setSize(const float width, const float height)
{
  auto size(_texture->getSize());
  _rectangle->setSize(sf::Vector2f(width / size.x, height / size.y));
  _sprite->setScale(sf::Vector2f(width / size.x, height / size.y));
}


void Image::setScale(const sf::Vector2f size)
{
  _rectangle->setScale(size);
  _sprite->setScale(size);
}


void Image::setScale(const float width, const float height)
{
  _rectangle->setScale(sf::Vector2f(width, height));
  _sprite->setScale(sf::Vector2f(width, height));
}


void Image::setScale(const float ratio)
{
  _rectangle->setScale(sf::Vector2f(ratio, ratio));
  _sprite->setScale(sf::Vector2f(ratio, ratio));
}


bool Image::load()
{
  if (_loaded) {
  	return true;
  }

  if (!_texture) {
    _texture = std::make_shared<sf::Texture> ();
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

  sf::Vector2f pos; // Sprite position
  using p = graphics::MapGraphicsProperties;
  pos.x = c.c * p::cellWidth()  + p::gridOffsetX();
  pos.y = c.l * p::cellHeight() + p::gridOffsetY();
  _sprite->setPosition(pos);

  if (load()) {
    graphics::GraphicsEngine::draw(_sprite);
  }

  graphics::GraphicsEngine::draw(_rectangle);
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
