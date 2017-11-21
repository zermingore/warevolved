#include <interface/MiniMap.hh>
#include <interface/Cursor.hh>
#include <game/Map.hh>
#include <graphics/GraphicsEngine.hh>
#include <graphics/Sprite.hh>
#include <game/Cell.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/Player.hh>



namespace interface {

MiniMap::MiniMap(graphics::Size2 size,
                 std::shared_ptr<const Map> map,
                 std::shared_ptr<const Cursor> cursor)
  : InterfaceElement("frame_thumbnail")
  , _frameSize(size)
  , _map(*map)
  , _playerCursor(*cursor)
{
}



void MiniMap::update()
{
}



void MiniMap::draw()
{
  using namespace graphics;

  // Draw the frame
  _sprite->setPosition(_position.x, _position.y);
  _sprite->setSize(_frameSize);
  _sprite->draw();


  // Computing the size of a cell
  const auto size_col((_frameSize.x - 10)
                      / static_cast<component> (_map.nbColumns()));
  const auto size_line((_frameSize.y - 10)
                       / static_cast<component> (_map.nbLines()));

  // List of players to get their color
  const auto players { game::Status::battle()->players() };

  const Size2 cell_size(size_col, size_line);


  const auto cells(_map.cells());
  for (auto col(0u); col < _map.nbColumns(); ++col)
  {
    for (auto line(0u); line < _map.nbLines(); ++line)
    {
      const auto c { cells[col][line] };
      const Pos2 pos {
        5 + _position.x + size_col  * static_cast<component> (col),
        5 + _position.y + size_line * static_cast<component> (line)
      };

      // Draw the terrain
      switch (c->terrain())
      {
        default:
          auto img { std::make_shared<Sprite> ("forest") };
          img->setPosition(pos.x, pos.y);
          img->setSize(cell_size);
          img->draw();
          break;
      }

      // Draw the units
      const auto unit {c->unit()};
      if (unit)
      {
        auto img { std::make_shared<Sprite> ("minimap_unit") };
        img->setPosition(pos.x, pos.y);
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
  _position = { static_cast<graphics::component> (pos.x),
                static_cast<graphics::component> (pos.y) };
}

} // namespace interface
