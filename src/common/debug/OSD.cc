#include <common/debug/OSD.hh>
#include <resources/ResourcesManager.hh>
#include <common/Status.hh>
#include <interface/Interface.hh>
#include <graphics/GraphicsEngine.hh>


namespace debug {


// Static attributes definition
Coords OSD::_dataPosition;
std::vector<std::shared_ptr<sf::Drawable>> OSD::_drawables;
unsigned int OSD::_fontSize = 20;



void OSD::addData(const std::string str)
{
  auto label(text(str));
  _drawables.push_back(label);
}


void OSD::addData(const int value)
{
  auto label(text(std::to_string(value)));
  _drawables.push_back(label);
}


// template<typename T>
// void OSD::addData(T data) {
//   _drawables.push_back(data);
// }


void OSD::draw()
{
  /// \todo draw a background

  for (auto it: _drawables) {
    graphics::GraphicsEngine::draw(it);
  }
}


std::shared_ptr<sf::Text> OSD::text(std::string str)
{
  auto label(std::make_shared<sf::Text> (
               str,
               resources::ResourcesManager::font("font_army"),
               _fontSize));

  label->setPosition(_dataPosition.x, _dataPosition.y);
  _dataPosition.y += _fontSize + 5;

  return label;
}


}; // namespace debug
