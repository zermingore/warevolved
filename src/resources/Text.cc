/**
 * \file
 * \author Zermingore
 * \date Sept 11, 2017
 * \namespace resources
 * \brief Text class declaration, used to draw strings
 */

#include <resources/Text.hh>

#include <graphics/GraphicsEngine.hh>
#include <resources/ResourcesManager.hh>



namespace resources {


Text::Text(const std::string& str,
           size_t size,
           graphics::Pos2 pos,
           const std::string& font)
  : _string(str)
  , _size(size)
  , _font(ResourcesManager::getFont(font))
  , _text(std::make_shared<sf::Text> (str, *(_font->getFont()), _size))
{
  _text->setPosition({pos.x, pos.y});
}



graphics::Size2 Text::getSize()
{
  return { _text->getLocalBounds().width, _text->getLocalBounds().height };
}



void Text::setPosition(graphics::Pos2 pos)
{
  _text->setPosition(pos.x, pos.y);
}



void Text::setPosition(graphics::component x, graphics::component y)
{
  _text->setPosition({x, y});
}



void Text::setColor(graphics::Color color)
{
  _text->setFillColor(color);
}



void Text::draw()
{
  graphics::GraphicsEngine::draw(_text);
}


} // namespace resources
