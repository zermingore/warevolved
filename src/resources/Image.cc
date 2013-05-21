#include <resources/Image.hh>
#include <common/globals.hh>


Image::Image() {
  std::cerr << "Invalid Default Ctor for now" << std::endl;
}


Image::Image(const std::string file_name,
			 const std::string name,
			 unsigned int id) :
  _texture (NULL),
  _sprite (NULL),
  _width (0),
  _height (0)
{
  _rectangle = new sf::RectangleShape(); // TODO allocation only if needed
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


Image::~Image()
{
# ifdef DEBUG
  std::cout << "Image Dtor" << std::endl;
# endif
  if (_rectangle)
	delete _rectangle;

  if (_texture)
	delete _texture;

  if (_sprite)
	delete _sprite;
}


sf::Texture *Image::getTexture()
{
  if (!_texture)
  {
	_texture = new sf::Texture();
	_texture->loadFromFile(_fileName);
	_rectangle->setTexture(_texture);
	_loaded = true;
  }

  return _texture;
}

void Image::initTexture()
{
  _texture = new sf::Texture();
  _texture->loadFromFile(_fileName);
  _rectangle->setTexture(_texture);
  _loaded = true;
}

void Image::initSprite()
{
  _sprite = new sf::Sprite(*_texture);
  _loaded = true;
}

sf::Sprite *Image::getSprite()
{
  if (!_texture)
	this->initTexture();

  if (!_sprite)
	this->initSprite();

  return _sprite;
}


void Image::setFileName(std::string file_name)
{
  _fileName = file_name;
  _loaded = false;
}


void Image::setSprite(sf::Sprite *sprite) {
  _sprite = sprite;
}

void Image::setSize(sf::Vector2f size) {
  _rectangle->setSize(size);
}

void Image::setPosition(sf::Vector2f position)
{
  if (!_sprite)
	this->initSprite();
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
	_texture = new sf::Texture();

  _texture->loadFromFile(_fileName);
  _rectangle->setTexture(_texture);
  _loaded = true;

  return false;
}


void Image::unload()
{
  if (!_texture)
	return;

  delete _texture;
  _loaded = false;

# ifdef DEBUG
  _rectangle->setTexture(NULL);
#endif

  return;
}

void Image::reload(std::string file_name)
{
  if (_texture)
	delete _texture;

  _texture->loadFromFile(file_name);
  _rectangle->setTexture(_texture);
  _loaded = true;
}


// void Image::draw(unsigned int pos_x, unsigned int pos_y,
// 				 unsigned int size_x, unsigned int size_y)
// {
//   _rectangle->setPosition(sf::Vector2f(pos_x, pos_y));
//   _rectangle->setSize(sf::Vector2f(size_x, size_y));

//   this->load();
//   //_window->draw(&_rectangle);
// }


void Image::drawAtCell(unsigned int i, unsigned int j)
{
  _rectangle->setPosition(
  	sf::Vector2f(i * g_status->getCellWidth()
				 + g_status->getGridThickness()
				 + g_status->getGridOffsetX(),

  				 j * g_status->getCellHeight()
				 + g_status->getGridThickness()
				 + g_status->getGridOffsetY()));

  _rectangle->setSize(sf::Vector2f(g_status->getCellWidth(), g_status->getCellHeight()));

  if (!_sprite)
	this->getSprite();

  if (this->load())
	g_status->getWindow()->draw(*_rectangle);
}


void Image::draw()
{
  // _rectangle->setPosition(_sprite->position);
  // _rectangle->setSize(_sprite->position);

  if (!_sprite)
	this->getSprite();

  if (this->load())
	g_status->getWindow()->draw(*_sprite);
}
