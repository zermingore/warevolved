#include <game/PathFinding.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/Unit.hh>
#include <resources/Image.hh>


PathFinding::PathFinding(std::shared_ptr<Map> map) :
  _map (map),
  _origin (0, 0),
  _current (0, 0),
  _maxLength (0),
  _currentLength (0)
{
}

void PathFinding::setOrigin(Coords coords,
                            std::shared_ptr<Unit> unit)
{
  clearPath();

  _unit = unit;
  _unit->setTargetIndex(0);

  _origin = coords;
  _current = coords;
  _currentLength = 0;
  _maxLength = _unit->motionValue();

  showAllowedPath();
}


void PathFinding::drawPath()
{
  _current = _origin;
  size_t i = 0;
  for (auto it = _directions.begin(); it != _directions.end(); ++it)
  {
    updateCurrentCell(*it);
    // TODO manage cache and image sprites
    // _images[i++]->drawAtCell(_currentX, _currentY);
    getImage(i++).draw();
  }
}


void PathFinding::clearPath()
{
  _directions.clear();
  deleteImagesVector();
  hideAllowedPath();

  // TODO clear only if we made a path request on a new cell
  // (to avoid clearing the path on selecting the same unit two times in a row)
}


void PathFinding::updateCurrentCell(direction direction)
{
  switch (direction)
  {
  case direction::UP:
      --_current.y;
      return;

    case direction::DOWN:
      ++_current.y;
      return;

    case direction::LEFT:
      --_current.x;
      return;

    case direction::RIGHT:
      ++_current.x;
      return;

    default:
      return;
  }
}

void PathFinding::buildImageVector()
{
  // manage 'riding' the path (increment a global index)
  // deleteImagesVector();

  unsigned int i = 0;
  for (auto it: _directions) // NOTE unused it
    _images.push_back(getImage(i++));
}


path_shape PathFinding::getShape(size_t index)
{
  // last element case
  if (index + 1 == _directions.size())
    return (static_cast <path_shape> (static_cast<int >(_directions[index]) - 360));

  direction next = _directions[index + 1];

  // same element as next case
  if (_directions[index] == next)
    return (static_cast <path_shape> (_directions[index]));

  // reverse
  if (std::abs(static_cast<int >(_directions[index]) - static_cast<int >(next)) == 180)
    return (static_cast <path_shape> (next));

  // from here, we know the direction changed
  switch (_directions[index])
  {
    case direction::UP:
      if (next == direction::RIGHT)
        return path_shape::CORNER_RIGHT_DOWN;
      return path_shape::CORNER_DOWN_LEFT;

    case direction::DOWN:
      if (next == direction::RIGHT)
        return path_shape::CORNER_UP_RIGHT;
      return path_shape::CORNER_LEFT_UP;

    case direction::LEFT:
      if (next == direction::UP)
        return path_shape::CORNER_UP_RIGHT;
      return path_shape::CORNER_RIGHT_DOWN;

    default:
      if (next == direction::UP)
        return path_shape::CORNER_LEFT_UP;
      return path_shape::CORNER_DOWN_LEFT;
    }
}


graphics::Image PathFinding::getImage(size_t index)
{
  return graphics::Image();
  // TODO up to GraphicsEngine

  // Image img; // TODO use a copy Ctor (avoid rotating all sprites)
  // unsigned int angle = 0;
  // path_shape shape = getShape(index);

  // switch (shape)
  // {
  //    // Rectangles
  //    case path_shape::UP:
  //    case path_shape::DOWN:
  //    case path_shape::LEFT:
  //    case path_shape::RIGHT:
  //      img = GETIMAGE("path_shape");
  //      break;

  //    // Arrows
  //    case path_shape::LAST_UP:
  //    case path_shape::LAST_DOWN:
  //    case path_shape::LAST_LEFT:
  //    case path_shape::LAST_RIGHT:
  //      img = GETIMAGE("path_arrow");
  //      break;

  //    // Corners
  //    default:
  //      img = GETIMAGE("path_corner");
  //      break;
  // }

  // angle = static_cast <unsigned int> (shape % 360);
  // img.sprite()->setRotation(angle);
  // img.sprite()->setOrigin(CELL_WIDTH / 2, CELL_HEIGHT / 2);

  // // drawing at the middle of the cell
  // sf::Vector2f pos;
  // pos.x = _current.x * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X + CELL_WIDTH / 2;
  // pos.y = _current.y * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y + CELL_HEIGHT / 2;
  // img.sprite()->setPosition(pos);

  //  return img;
}

void PathFinding::addNextDirection(direction direction)
{
  _directions.push_back(direction);
  ++_currentLength;
}


void PathFinding::showAllowedPath()
{
  std::stack<std::pair<size_t, size_t>> s;
  s.push(std::pair<size_t, size_t>(_unit->x(), _unit->y()));
  _reachableCells.clear();
  std::vector<std::pair<size_t, size_t>> checked;

  while (!s.empty())
  {
    // getting Cell's coordinates (stack of Coordinates)
    size_t x = s.top().first;
    size_t y = s.top().second;
    s.pop();

    // check overflow, Manhattan distance and if we already marked the cell
    if (x < 0 || y < 0 || x > _map->nbColumns() - 1 || y > _map->nbLines() - 1
        || std::abs(_unit->x() - x) + std::abs(_unit->y() - y) > _maxLength
        || std::find(checked.begin(), checked.end(), std::pair<size_t, size_t>(x, y)) != checked.end())
    {
      continue;
    }
;
    _reachableCells.push_back(_map->cell(x, y));
    checked.push_back(std::pair<size_t, size_t>(x, y));

    s.emplace(std::pair<size_t, size_t>(x + 1, y));
    s.emplace(std::pair<size_t, size_t>(x, y + 1));
    s.emplace(std::pair<size_t, size_t>(x - 1, y));
    s.emplace(std::pair<size_t, size_t>(x, y - 1));
  }

  highlightCells();
}


void PathFinding::highlightCells()
{
  // TODO check _unit's inventory
  //   (do not color enemies in red if we can't shoot them,
  //    color allies in a different color if we can heal them, ...)
  for (auto it: _reachableCells)
  {
    std::shared_ptr<Cell> c = _map->cell(it->x(), it->y());

    c->setHighlight(true);
    if (c->unit())
    {
     if (c->unit()->playerId() != _map->currentPlayer())
     {
       c->setHighlightColor(sf::Color::Red);
       _unit->targets()->push_back(c);
     }
     else
       c->setHighlightColor(sf::Color::Green);
    }
    else
      c->setHighlightColor(sf::Color::Yellow);
  }

  // highlight reachable targets
  // for (auto unit: MAP->players.units())
  // {}
}


void PathFinding::hideAllowedPath() const
{
  // cleaning displayed move possibilities
  for (unsigned int i = 0; i < _map->nbColumns(); ++i)
    for (unsigned int j = 0; j < _map->nbLines(); ++j)
      _map->cell(i, j)->setHighlight(false);
}
