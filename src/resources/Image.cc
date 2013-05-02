#include <resources/Image.hh>


Image::Image() {
  std::cerr << "Invalid Default Ctor for now" << std::endl;
}


Image::Image(const std::string file_name,
			 const std::string name,
			 unsigned int id) :
  _texture (NULL),
  _width (0),
  _height (0)
{
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

  if (_texture)
	delete _texture;

  delete _rectangle;
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


void Image::setFileName(std::string file_name)
{
  _fileName = file_name;
  _loaded = false;
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

  return;
}


void Image::draw(unsigned int pos_x, unsigned int pos_y,
				 unsigned int size_x, unsigned int size_y);
{
  _rectangle->setPosition(sf::Vector2f(pos_x, pos_y));
  _rectangle->setSize(sf::Vector2f(size_x, size_y));

  this->load();
  _window->draw(&_rectangle);
}
