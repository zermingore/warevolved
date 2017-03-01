#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/Unit.hh>
#include <resources/Image.hh>
#include <common/Status.hh>
#include <common/enums/directions.hh>
#include <common/enums/path_shapes.hh>
#include <graphics/MapGraphicsProperties.hh>


// static members definition
std::shared_ptr<Map> PathFinding::_map;
std::shared_ptr<Unit> PathFinding::_unit;

Coords PathFinding::_origin;
Coords PathFinding::_current;

size_t PathFinding::_maxLength;
size_t PathFinding::_currentLength;

std::vector<e_direction> PathFinding::_directions;
std::vector<std::shared_ptr<resources::Image>> PathFinding::_images;
std::vector<std::shared_ptr<Cell>> PathFinding::_reachableCells;
std::vector<std::shared_ptr<Cell>> PathFinding::_enemyPositions;



void PathFinding::setOrigin(Coords coords, std::shared_ptr<Unit> unit)
{
  assert(unit && "PathFinding: No unit provided");

  clearPath();

  _enemyPositions.clear();

  _unit = unit;
  _origin = coords;
  _current = coords;
  _currentLength = 0;
  _maxLength = unit->motionValue();

  computeAllowedPath();
  highlightCells();
}


void PathFinding::drawPath()
{
  _current = _origin;
  size_t i = 0;
  for (auto it(_directions.begin()); it != _directions.end(); ++it)
  {
    updateCurrentCell(*it);
    /// \todo manage cache and image sprites
    // _images[i++]->drawAtCell(_currentX, _currentY);
    getImage(i++)->draw(); /// \todo drawAtCell
  }
}


void PathFinding::clearPath()
{
  _directions.clear();
  deleteImagesVector();
  hideAllowedPath();

  /// \todo clear only if we made a path request on a new cell
  // (to avoid clearing the path on selecting the same unit two times in a row)
}


void PathFinding::updateCurrentCell(e_direction direction)
{
  switch (direction)
  {
    case e_direction::UP:
      --_current.y;
      return;

    case e_direction::DOWN:
      ++_current.y;
      return;

    case e_direction::LEFT:
      --_current.x;
      return;

    case e_direction::RIGHT:
      ++_current.x;
      return;

    default:
      ERROR("Invalid direction", (int) direction);
      std::exit(1);
  }
}

void PathFinding::buildImageVector()
{
  // manage 'riding' the path (increment a global index)
  // deleteImagesVector();

  for (auto i(0u); i < _directions.size(); ++i) {
    _images.push_back(getImage(i));
  }
}


e_path_shape PathFinding::getShape(size_t index)
{
  // last element case
  if (index + 1 == _directions.size())
  {
    return (static_cast <e_path_shape> (
              static_cast<int> (_directions[index]) - 360));
  }

  e_direction next = _directions[index + 1];

  // same element as next case
  if (_directions[index] == next) {
    return (static_cast <e_path_shape> (_directions[index]));
  }

  // reverse
  if (std::abs(static_cast<int> (_directions[index]) - static_cast<int> (next)) == 180) {
    return (static_cast <e_path_shape> (next));
  }

  // from here, we know the direction changed
  switch (_directions[index])
  {
    case e_direction::UP:
      return next == e_direction::RIGHT
        ? e_path_shape::CORNER_RIGHT_DOWN
        : e_path_shape::CORNER_DOWN_LEFT;

    case e_direction::DOWN:
      return next == e_direction::RIGHT
        ? e_path_shape::CORNER_UP_RIGHT
        : e_path_shape::CORNER_LEFT_UP;

    case e_direction::LEFT:
      return next == e_direction::UP
        ? e_path_shape::CORNER_UP_RIGHT
        : e_path_shape::CORNER_RIGHT_DOWN;

    default:
      return next == e_direction::UP
        ? e_path_shape::CORNER_LEFT_UP
        : e_path_shape::CORNER_DOWN_LEFT;
    }
}


std::shared_ptr<resources::Image> PathFinding::getImage(size_t index)
{
  std::shared_ptr<resources::Image> img;
  e_path_shape shape = getShape(index);

  switch (shape)
  {
     // Rectangles
     case e_path_shape::UP:
     case e_path_shape::DOWN:
     case e_path_shape::LEFT:
     case e_path_shape::RIGHT:
       img = resources::ResourcesManager::getImage("path_shape");
       break;

     // Arrows
     case e_path_shape::LAST_UP:
     case e_path_shape::LAST_DOWN:
     case e_path_shape::LAST_LEFT:
     case e_path_shape::LAST_RIGHT:
       img = resources::ResourcesManager::getImage("path_arrow");
       break;

     // Corners
     default:
       img = resources::ResourcesManager::getImage("path_corner");
       break;
  }

  using p = graphics::MapGraphicsProperties;

  unsigned int angle(static_cast<int> (shape) % 360);
  img->sprite()->setRotation(angle);
  img->sprite()->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  // drawing at the middle of the cell
  sf::Vector2f pos(
    _current.x * p::cellWidth()  + p::gridThickness() + p::gridOffsetX() + p::cellWidth()  / 2,
    _current.y * p::cellHeight() + p::gridThickness() + p::gridOffsetY() + p::cellHeight() / 2);

  img->sprite()->setPosition(pos);

  return img;
}

void PathFinding::addNextDirection(e_direction direction)
{
  _directions.push_back(direction);
  ++_currentLength;
}


void PathFinding::computeAllowedPath()
{
  // implicit cast into integer to handle negative values: unit_x - cell_x
  int unit_x = _unit->x();
  int unit_y = _unit->y();

  std::stack<std::pair<int, int>> s;
  s.push(std::pair<int, int>(unit_x, unit_y));

  _reachableCells.clear();
  std::vector<std::pair<int, int>> checked; // already visited cells

  while (!s.empty())
  {
    // getting Cell's coordinates (stack of Coordinates)
    auto current_cell = s.top();
    int x = current_cell.first;
    int y = current_cell.second;
    s.pop();

    // check overflow, Manhattan distance and if we already marked the cell
    if (   static_cast<size_t> (x) >= _map->nbColumns()
        || static_cast<size_t> (y) >= _map->nbLines()
        || std::abs(unit_x - x) + std::abs(unit_y - y) > static_cast<int> (_maxLength)
        || std::find(checked.begin(), checked.end(), current_cell) != checked.end())
    {
      // skipping invalid cells
      continue;
    }

    _reachableCells.push_back((*_map)[x][y]);
    checked.push_back(current_cell);

    // continuing with the four adjacent cells of the current one
    s.emplace(x + 1, y    );
    s.emplace(x    , y + 1);
    s.emplace(x - 1, y    );
    s.emplace(x    , y - 1);
  }
}


void PathFinding::highlightCells()
{
  /// \todo check _unit's inventory
  //   (do not color enemies in red if we can't shoot them,
  //    color allies in a different color if we can heal them, ...)
  for (auto it: _reachableCells)
  {
    auto c = (*_map)[it->x()][it->y()];

    c->setHighlight(true);
    if (c->unit())
    {
      if (c->unit()->playerId() != Status::player()->id())
      {
        c->setHighlightColor(sf::Color::Red);
        _enemyPositions.push_back(c);
      }
      else {
        c->setHighlightColor(sf::Color::Green);
      }
    }
    else {
      c->setHighlightColor(sf::Color::Yellow);
    }
  }
}


void PathFinding::hideAllowedPath()
{
  // cleaning displayed move possibilities
  for (auto i(0u); i < _map->nbColumns(); ++i)
  {
    for (auto j(0u); j < _map->nbLines(); ++j) {
      (*_map)[i][j]->setHighlight(false);
    }
  }
}


bool PathFinding::allowedMove()
{
  /// \todo complete receiving direction request
  // at the moment it's only checking the path length
  return _currentLength < _maxLength;
}


bool PathFinding::allowedAttack(std::shared_ptr<Unit> unit, Coords c)
{
  if (_enemyPositions.empty()) {
    return false;
  }

  // For every unit, if it's not in the same team as the given unit,
  //   check if it's at attack range

  // forcing signed values to allow negative values
  int unit_x(c.x);
  int unit_y(c.y);

  for (auto cell: _enemyPositions)
  {
    /// \todo take into account min range

    // Implicit cast into signed type to handle negative values
    int x(cell->x());
    int y(cell->y());

    // checking Manhattan distance
    if (std::abs(unit_x - x) + std::abs(unit_y - y)
        > static_cast<int> (unit->maxRange()))
    {
      continue;
    }

    return true;
  }

  return false;
}



std::shared_ptr<std::vector<std::shared_ptr<Cell>>>
PathFinding::getTargets(std::shared_ptr<Unit> unit, std::shared_ptr<Cell> cell)
{
  assert(unit && cell);

  std::vector<std::shared_ptr<Cell>> targets_list;

  // implicit cast into integer to handle negative values: unit_c - cell_c
  int unit_c = cell->c();
  int unit_l = cell->l();

  std::stack<std::pair<int, int>> s;
  s.push(std::pair<int, int> (unit_c, unit_l));

  std::vector<std::pair<int, int>> checked; // already visited cells

  // adding the 4 cells adjacent to the attacker
  s.emplace(unit_c + 1, unit_l    );
  s.emplace(unit_c    , unit_l + 1);
  s.emplace(unit_c - 1, unit_l    );
  s.emplace(unit_c    , unit_l - 1);

  while (!s.empty())
  {
    // getting Cell's coordinates (stack of Coordinates)
    auto current_cell = s.top();
    int c = current_cell.first;
    int l = current_cell.second;
    s.pop();

    // check overflow, Manhattan distance and if we already marked the cell
    size_t distance(std::abs(unit_c - c) + std::abs(unit_l - l));
    if (   static_cast<size_t> (c) >= _map->nbColumns()
        || static_cast<size_t> (l) >= _map->nbLines()
        || distance < unit->minRange()
        || distance > unit->maxRange()
        || std::find(checked.begin(), checked.end(), current_cell) != checked.end())
    {
      // skipping invalid cells
      continue;
    }

    checked.push_back(current_cell);

    // updating target list
    auto map_cell = (*_map)[c][l];
    if (map_cell->unit())
    {
      if (map_cell->unit()->playerId() != Status::player()->id()) {
        targets_list.push_back(map_cell);
      }
    }

    // continuing with the four adjacent cells of the current one
    s.emplace(c + 1, l    );
    s.emplace(c    , l + 1);
    s.emplace(c - 1, l    );
    s.emplace(c    , l - 1);
  }

  return std::make_shared<std::vector<std::shared_ptr<Cell>>> (targets_list);
}
