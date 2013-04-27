#include <resources/Image.hh>


Image::Image() :
  _x (0),
  _y (0)
{
  std::cerr << "Invalid Ctor for now" << std::endl;
}


Image::Image(const std::string file_name,
			 const std::string name,
			 unsigned int id)
{
  _id = id;
  _fileName = file_name;
  _name = name;
  _loaded = false;
  _scope = E_SCOPE_ALL;

  _texture = new sf::Texture();
  //_texture->loadFromFile(_fileName);
}


Image::~Image()
{
  //this->unload(_fileName);
}


bool Image::load()
{
  if (_loaded)
  	return true;

  if (!_texture)
  {
	_texture = new sf::Texture();
	// delete _texture;
  }

  // _texture->loadFromFile(_fileName);

  return false;
}

bool Image::unload()
{
  return true;
}
