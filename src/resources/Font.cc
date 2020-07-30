#include <graphics/graphic_types.hh>
#include <resources/Font.hh>


namespace resources {


Font::Font(const std::string& file_name, const std::string& name)
  : _font(std::make_shared<graphics::Font> ())
{
  _fileName = file_name;
  _name = name;
  _font->loadFromFile(_fileName);
}



std::shared_ptr<graphics::Font> Font::getFont()
{
  return _font;
}


} // namespace resources
