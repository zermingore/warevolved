#include <graphics/graphic_types.hh>
#include <resources/Font.hh>


namespace resources {


Font::Font(const std::string& file_name, const std::string& name)
  : _font (nullptr)
{
  _fileName = file_name;
  _name = name;
  _loaded = false;
}


bool Font::load()
{
  if (_loaded) {
    return true;
  }

  _font = std::make_shared<graphics::Font> ();
  _font->loadFromFile(_fileName);
  _loaded = true;

  return false;
}


std::shared_ptr<graphics::Font> Font::getFont()
{
  if (!_loaded) {
    this->load();
  }

  return _font;
}


} // namespace resources
