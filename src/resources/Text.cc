#include <resources/Text.hh>

#include <resources/ResourcesManager.hh>
#include <graphics/GraphicsEngine.hh>



namespace resources {


Text::Text(std::string str, int size, graphics::Pos2 pos, std::string font)
  : _string(str)
  , _size(size)
  , _position(pos)
{
  _font = ResourcesManager::getFont(font);
  _text = std::make_shared<sf::Text> (str, *(_font->getFont()), _size);
  _text->setPosition(pos);
}



void Text::draw()
{
  graphics::GraphicsEngine::draw(_text);
}



} // namespace resources
