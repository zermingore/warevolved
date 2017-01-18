#include <resources/Image.hh>
#include <graphics/GraphicsEngine.hh>


namespace graphics {


Image::Image(const std::string file_name,
             const std::string name)
{
   /// \todo allocation only if needed (using a proxy)
  _rectangle = std::make_shared<sf::RectangleShape> ();
  _rectangle->setPosition(sf::Vector2f(0, 0));
  _rectangle->setSize(sf::Vector2f(0, 0));

   /// \todo in debug, load an ugly texture to help noticing it
# ifdef DEBUG
  _rectangle->setTexture(NULL);
# else
  _rectangle->setTexture(NULL);
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


void Image::setFileName(std::string file_name)
{
  _fileName = file_name;
  _loaded = false;
}


void Image::setPosition(sf::Vector2f position)
{
  if (!_sprite) {
    initSprite();
  }
  _sprite->setPosition(position);
}


void Image::setPosition(Coords position)
{
  if (!_sprite) {
    initSprite();
  }
  _sprite->setPosition(sf::Vector2f(position.x, position.y));
}



void Image::setSize(sf::Vector2f size)
{
  auto old_size(_rectangle->getSize());
  _rectangle->setSize(size);
  _sprite->setScale(sf::Vector2f(size.x / old_size.x, size.y / old_size.y));
}

void Image::setSize(float width, float height)
{
  auto size(_texture->getSize());
  _rectangle->setSize(sf::Vector2f(width / size.x, height / size.y));
  _sprite->setScale(sf::Vector2f(width / size.x, height / size.y));
}



void Image::setScale(sf::Vector2f size)
{
  _rectangle->setScale(size);
  _sprite->setScale(size);
}

void Image::setScale(float width, float height)
{
  _rectangle->setScale(sf::Vector2f(width, height));
  _sprite->setScale(sf::Vector2f(width, height));
}


void Image::setScale(float ratio)
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
  _rectangle->setTexture(NULL);
# endif

  return;
}


void Image::reload(std::string file_name)
{
  // if (_texture)
  //   delete _texture;

  _texture->loadFromFile(file_name);
  _rectangle->setTexture(_texture.get());
  _loaded = true;
}


void Image::drawAtCell(const Coords c,
                       const std::shared_ptr<Map::MapGraphicsProperties> p)
{
  if (!_sprite) {
    sprite();
  }

  // Sprite position
  sf::Vector2f pos;
  pos.x = c.x * p->cellWidth()  + p->gridOffsetX();
  pos.y = c.y * p->cellHeight() + p->gridOffsetY();
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


} // namespace graphics
