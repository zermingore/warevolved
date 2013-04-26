#include <resources/Image.hh>


Image::Image() :
  _x (0),
  _y (0)
{
}


Image::Image(const std::string file_name, unsigned int id)
{
  _id = id;
//  _fileName = file_name;
  _loaded = false;
  _scope = E_SCOPE_ALL;

  //_texture = new sf::Texture();
  // _texture->loadFromFile(_fileName);

  this->load();
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
	_texture = new sf::Texture();

  // _texture->loadFromFile(_fileName);
  // std::cout << "<<<" << _fileName << std::endl;


  return false;
}

bool Image::unload()
{
  return true;
}
