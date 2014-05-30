#include <resources/Image.hh>
#include <common/globals.hh>


Image::Image(const std::string file_name,
             const std::string name,
             unsigned int id) :
  _width (0),
  _height (0)
{
  _rectangle.reset(new sf::RectangleShape()); // TODO allocation only if needed
  _rectangle->setPosition(sf::Vector2f(0, 0));
  _rectangle->setSize(sf::Vector2f(0, 0));

  // in debug, load an ugly texture to help noticing it
# ifdef DEBUG
  _rectangle->setTexture(NULL);
# else
  _rectangle->setTexture(NULL);
# endif

  _id = id;
  _fileName = file_name;
  _name = name;
  _loaded = false;
  _scope = E_SCOPE_ALL;
}

std::shared_ptr<sf::Texture> Image::getTexture()
{
  if (!_texture)
  {
    _texture.reset(new sf::Texture());
    _texture->loadFromFile(_fileName);
    _rectangle->setTexture(_texture.get());
    _loaded = true;
  }

  return _texture;
}

void Image::initTexture()
{
  _texture.reset(new sf::Texture());
  _texture->loadFromFile(_fileName);
  _rectangle->setTexture((sf::Texture *) (_texture.get()));
  _loaded = true;
}

void Image::initSprite()
{
  _sprite.reset(new sf::Sprite(*_texture));
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


void Image::setSize(sf::Vector2f size) {
  _rectangle->setSize(size);
}

void Image::setPosition(sf::Vector2f position)
{
  if (!_sprite)
    initSprite();
  _sprite->setPosition(position);
}

void Image::setSize(float width, float height) {
  _rectangle->setSize(sf::Vector2f(width, height));
}


bool Image::load()
{
  if (_loaded)
  	return true;

  if (!_texture)
    _texture.reset(new sf::Texture());

  _texture->loadFromFile(_fileName);
  _rectangle->setTexture(_texture.get());
  _loaded = true;

  return false;
}


void Image::unload()
{
  if (!_texture)
    return;

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


/// \deprecated use Coords
void Image::drawAtCell(unsigned int i, unsigned int j)
{
  if (!_sprite)
    sprite();

  // Sprite position
  sf::Vector2f pos;
  pos.x = i * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X;
  pos.y = j * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y;
  _sprite->setPosition(pos);

  if (load())
    WINDOW->draw(*_sprite);
  WINDOW->draw(*_rectangle);
}


void Image::drawAtCell(Coords c)
{
  if (!_sprite)
    sprite();

  // Sprite position
  sf::Vector2f pos;
  pos.x = c.x * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X;
  pos.y = c.y * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y;
  _sprite->setPosition(pos);

  if (load())
    WINDOW->draw(*_sprite);
  WINDOW->draw(*_rectangle);
}


void Image::draw()
{
  if (!_sprite)
    sprite();

  _rectangle->setPosition(_sprite->getPosition());

  if (load())
    WINDOW->draw(*_sprite);
  WINDOW->draw(*_rectangle);
}
