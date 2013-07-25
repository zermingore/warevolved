#include <resources/Font.hh>
#include <common/constants.hh>


Font::Font(const std::string file_name,
		   const std::string name,
		   unsigned int id)
{
  _id = id;
  _fileName = file_name;
  _name = name;
  _loaded = false;
}

Font::~Font()
{
//  if (_font)
//    delete _font;
}

bool Font::load()
{
  if (_loaded)
    return true;

  if (!_font)
    _font = new sf::Font();

  _font->loadFromFile(_fileName);
  _loaded = true;

  return false;
}

void Font::unload()
{
  return;
}


sf::Font *Font::getFont()
{
  if (!_loaded)
    this->load();

  return _font;
}
