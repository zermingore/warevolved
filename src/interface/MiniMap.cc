#include <interface/MiniMap.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>
#include <graphics/GraphicsEngine.hh>



namespace interface {

MiniMap::MiniMap(std::pair<size_t, size_t> size,
                 std::shared_ptr<const Map> map,
                 std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("frame_minimap")
  , _frameSize(size)
  , _map(map)
  , _playerCursor(cursor)
{
}



void MiniMap::update()
{
  _image->sprite()->setPosition(static_cast<float> (_position.x),
                                static_cast<float> (_position.y));
}



void MiniMap::draw()
{
  graphics::GraphicsEngine::draw(_image->sprite());
}



void MiniMap::setPosition(Coords pos)
{
  _position = pos;
}

} // namespace interface
