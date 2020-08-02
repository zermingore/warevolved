/**
 * \file
 * \date April 15, 2013
 * \author Zermingore
 * \brief OSD (On Screen Display) Debug information class implementation
 */

#include <debug/OSD.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <interface/Interface.hh>
#include <resources/ResourcesManager.hh>
#include <resources/Text.hh>


namespace debug {


// Static attributes definition
Coords OSD::_dataPosition;
std::vector<std::shared_ptr<sf::Drawable>> OSD::_drawables;
unsigned int OSD::_fontSize = 20;



void OSD::addStr(const std::string& str, const std::string& description)
{
  std::string desc;
  if (!description.empty())
  {
    desc = description + ": ";
  }

  addText(desc + str);
}


void OSD::draw()
{
  /// \todo draw a background

  for (const auto& it: _drawables) {
    graphics::GraphicsEngine::draw(it);
  }

  _drawables.clear();
  _dataPosition.y = 0;
}


void OSD::addText(const std::string& str)
{
  const graphics::Pos2 pos {
    static_cast<graphics::component> (_dataPosition.x),
    static_cast<graphics::component> (_dataPosition.y)
  };

  auto label = std::make_shared<resources::Text> (str, _fontSize, pos);
  _drawables.emplace_back(label->graphicalText());
  _dataPosition.y += _fontSize + 5;
}



void OSD::writeOnCell(size_t c, size_t l, const std::string& str)
{
  using p = graphics::MapGraphicsProperties;

  const graphics::Pos2 pos {
    static_cast<graphics::component> (c) * p::cellWidth()  + p::gridOffsetX(),
    static_cast<graphics::component> (l) * p::cellHeight() + p::gridOffsetY()
  };

  auto label = std::make_shared<resources::Text> (str, _fontSize, pos);
  _drawables.emplace_back(label->graphicalText());
}



} // namespace debug
