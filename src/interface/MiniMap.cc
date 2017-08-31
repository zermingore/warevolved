#include <interface/MiniMap.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>



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

}



void MiniMap::draw()
{

}


} // namespace interface
