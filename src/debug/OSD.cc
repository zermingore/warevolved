#include <debug/OSD.hh>
#include <resources/ResourcesManager.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>


namespace debug {


// Static attributes definition
Coords OSD::_dataPosition;
std::vector<std::shared_ptr<sf::Drawable>> OSD::_drawables;
unsigned int OSD::_fontSize = 20;



void OSD::addStr(const std::string str)
{
  auto label(text(str));
  _drawables.push_back(label);
}


void OSD::draw()
{
  /// \todo draw a background

  for (auto it: _drawables) {
    graphics::GraphicsEngine::draw(it);
  }

  _drawables.clear();
  _dataPosition.y = 0;
}


std::shared_ptr<sf::Text> OSD::text(const std::string str)
{
  auto label(std::make_shared<sf::Text> (
               str,
               resources::ResourcesManager::font("font_army"),
               _fontSize));

  label->setPosition(static_cast<float> (_dataPosition.x),
                     static_cast<float> (_dataPosition.y));

  _dataPosition.y += _fontSize + 5;

  return label;
}


} // namespace debug
