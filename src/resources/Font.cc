#include <resources/Font.hh>
#include <common/constants.hh>

Font::Font() {
}


Font::Font(const std::string file_name,
		   const std::string name,
		   unsigned int id)
{
  _id = id;
  _fileName = file_name;
  _name = name;
  _loaded = false;

//  this->load();
}


Font::~Font() {
}

bool Font::load()
{
  _font->loadFromFile(_fileName); // static_cast<std::string>(FONTS_FOLDER) + _fileName

  return true;
}


void Font::unload()
{
  return;
}
