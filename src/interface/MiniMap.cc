#include <interface/MiniMap.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/graphic_types.hh>
#include <game/Cell.hh>



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
  // Computing the size of a cell (using explicit size type)
  const size_t size_column(_frameSize.first / _map->nbColumns());
  const size_t size_line(_frameSize.second  / _map->nbLines());

  const auto cells(_map->cells());
  for (auto col(0u); col < _map->nbColumns(); ++col)
  {
    for (auto line(0u); line < _map->nbLines(); ++line)
    {
      const auto c {cells[col][line]};
      switch (c->terrain())
      {
        default:
          auto img(resources::ResourcesManager::getImage("forest"));
          img->setPosition({ _position.c + size_column * col,
                             _position.l + size_line * line });
          img->setSize(static_cast<graphics::component> (size_column),
                       static_cast<graphics::component> (size_line));
          img->draw();
          break;
      }

      // if (c->unit()) {
      //   drawUnit(c->unit());
      // }
    }
  }

}



void MiniMap::setPosition(Coords pos)
{
  _position = pos;
}

} // namespace interface
