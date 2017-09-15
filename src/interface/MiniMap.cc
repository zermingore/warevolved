#include <interface/MiniMap.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/graphic_types.hh>
#include <game/Cell.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Player.hh>



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

  // List of players to get their color
  const auto players { game::Status::battle()->players() };

  using namespace graphics;
  const Size2 cell_size(static_cast<component> (size_column),
                        static_cast<component> (size_line));

  const auto cells(_map->cells());
  for (auto col(0u); col < _map->nbColumns(); ++col)
  {
    for (auto line(0u); line < _map->nbLines(); ++line)
    {
      const auto c { cells[col][line] };
      const Coords pos { _position.c + size_column * col,
                         _position.l + size_line   * line };

      // Draw the terrain
      switch (c->terrain())
      {
        default:
          auto img { resources::ResourcesManager::getImage("forest") };
          img->setPosition(pos);
          img->setSize(cell_size);
          img->draw();
          break;
      }

      // Draw the units
      const auto unit {c->unit()};
      if (unit)
      {
        auto img { resources::ResourcesManager::getImage("minimap_unit") };
        img->setPosition(pos);
        img->setSize(cell_size);

        // Fade the color or use the color of the Player owning this Unit
        if (unit->played())
        {
          img->setColor(Color(127, 127, 127, 150));
        }
        else
        {
          img->setColor(players[unit->playerId()]->color());
        }

        img->draw();
      }
    }
  }
}



void MiniMap::setPosition(Coords pos)
{
  _position = pos;
}

} // namespace interface
