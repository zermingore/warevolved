#include <resources/Image.hh>

Image::Image() :
  _x (0),
  _y (0)
{
}

Image::~Image()
{
  //this->unload(_fileName);
}

bool Image::load()
{
  if (_loaded)
	return true;

  _texture->loadFromFile(_fileName + ".png"); // add extension in xml

  return false;
}

bool Image::unload()
{
  return true;
}
