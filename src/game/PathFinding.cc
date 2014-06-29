#include <game/PathFinding.hh>
#include <common/macros.hh>
#include <common/globals.hh>


PathFinding::PathFinding() :
  _origin (0, 0),
  _current (0, 0),
  _maxLength (0),
  _currentLength (0)
{
}

void PathFinding::setOrigin(Coords coords)
{
  clearPath();

  _unit = MAP.unit(coords);
  _unit->setTargetIndex(0);
  _unit->targets()->clear();

  _origin = coords;
  _current = coords;
  _currentLength = 0;
  _maxLength = _unit->motionValue();

  showAllowedPath();
}


void PathFinding::drawPath()
{
  _current = _origin;
  unsigned int i = 0;
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


void PathFinding::updateCurrentCell(e_direction direction)
{
  switch (direction)
  {
    case E_DIRECTION_UP:
      --_current.y;
      return;

    case E_DIRECTION_DOWN:
      ++_current.y;
      return;

    case E_DIRECTION_LEFT:
      --_current.x;
      return;

    case E_DIRECTION_RIGHT:
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
  for (auto it = _directions.begin(); it != _directions.end(); ++it)
    _images.push_back(getImage(i++));
}


e_path_shape PathFinding::getShape(unsigned int index)
{
  // last element case
  if (index + 1 == _directions.size())
    return (static_cast <e_path_shape> (_directions[index] - 360));

  e_direction next = _directions[index + 1];

  // same element as next case
  if (_directions[index] == next)
    return (static_cast <e_path_shape> (_directions[index]));

  // reverse
  if (std::abs(_directions[index] - next) == 180)
    return (static_cast <e_path_shape> (next));

  // from here, we know the direction changed
  switch (_directions[index])
  {
    case E_DIRECTION_UP:
      if (next == E_DIRECTION_RIGHT)
        return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_RIGHT_DOWN));
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_DOWN_LEFT));

    case E_DIRECTION_DOWN:
      if (next == E_DIRECTION_RIGHT)
        return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_UP_RIGHT));
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_LEFT_UP));

    case E_DIRECTION_LEFT:
      if (next == E_DIRECTION_UP)
        return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_UP_RIGHT));
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_RIGHT_DOWN));

    default:
      if (next == E_DIRECTION_UP)
        return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_LEFT_UP));
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_DOWN_LEFT));
    }
}


Image PathFinding::getImage(unsigned int index)
{
  Image img; // TODO use a copy Ctor (avoid rotating all sprites)
  unsigned int angle = 0;
  e_path_shape shape = getShape(index);

  switch (shape)
  {
     // Rectangles
     case E_PATH_SHAPE_UP:
     case E_PATH_SHAPE_DOWN:
     case E_PATH_SHAPE_LEFT:
     case E_PATH_SHAPE_RIGHT:
       img = GETIMAGE("path_shape");
       break;

     // Arrows
     case E_PATH_SHAPE_LAST_UP:
     case E_PATH_SHAPE_LAST_DOWN:
     case E_PATH_SHAPE_LAST_LEFT:
     case E_PATH_SHAPE_LAST_RIGHT:
       img = GETIMAGE("path_arrow");
       break;

     // Corners
     default:
       img = GETIMAGE("path_corner");
       break;
  }

  angle = static_cast <unsigned int> (shape % 360);
  img.sprite()->setRotation(angle);
  img.sprite()->setOrigin(CELL_WIDTH / 2, CELL_HEIGHT / 2);

  // drawing at the middle of the cell
  sf::Vector2f pos;
  pos.x = _current.x * CELL_WIDTH + GRID_THICKNESS + GRID_OFFSET_X + CELL_WIDTH / 2;
  pos.y = _current.y * CELL_HEIGHT + GRID_THICKNESS + GRID_OFFSET_Y + CELL_HEIGHT / 2;
  img.sprite()->setPosition(pos);

  return img;
}

void PathFinding::addNextDirection(e_direction direction)
{
  _directions.push_back(direction);
  ++_currentLength;
}


void PathFinding::showAllowedPath()
{
  std::stack<std::pair<int, int>> s;
  s.push(std::pair<int, int>(_unit->x(), _unit->y()));
  _reachableCells.clear();
  std::vector<std::pair<int, int>> checked;

  while (!s.empty())
  {
    // getting Cell's coordinates (stack of Coordinates)
    int x = s.top().first;
    int y = s.top().second;
    s.pop();

    // check overflow, Manhattan distance and if we already marked the cell
    if (x < 0 || y < 0 || x > (int) NB_COLUMNS - 1 || y > (int) NB_LINES - 1
        || std::abs((int) _unit->x() - x) + std::abs((int) _unit->y() - y) > _maxLength
        || std::find(checked.begin(), checked.end(), std::pair<int, int>(x, y)) != checked.end())
    {
      continue;
    }

    auto cells = CELLS;
    _reachableCells.push_back(cells[x][y]);
    checked.push_back(std::pair<int, int>(x, y));

    s.emplace(std::pair<int, int>(x + 1, y));
    s.emplace(std::pair<int, int>(x, y + 1));
    s.emplace(std::pair<int, int>(x - 1, y));
    s.emplace(std::pair<int, int>(x, y - 1));
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
    std::shared_ptr<Cell> c = CELLS[it->x()][it->y()];

    c->setHighlight(true);
    if (c->unit())
    {
     if (c->unit()->playerId() != g_status->currentPlayer())
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
}


void PathFinding::hideAllowedPath() const
{
  // cleaning displayed move possibilities
  std::vector<std::vector<std::shared_ptr<Cell>>> cells = CELLS;
  for (unsigned int i = 0; i < NB_COLUMNS; ++i)
    for (unsigned int j = 0; j < NB_LINES; ++j)
      cells[i][j]->setHighlight(false);
}
