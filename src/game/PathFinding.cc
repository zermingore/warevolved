#include <game/PathFinding.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/Unit.hh>
#include <resources/Image.hh>
#include <common/Status.hh>
#include <common/enums/directions.hh>
#include <common/enums/path_shapes.hh>
#include <graphics/graphics.hh>
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
      --_current.l;
      return;

    case e_direction::DOWN:
      ++_current.l;
      return;

    case e_direction::LEFT:
      --_current.c;
      return;

    case e_direction::RIGHT:
      ++_current.c;
      return;

    default:
      ERROR("Invalid direction", static_cast<int> (direction));
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


std::shared_ptr<resources::Image> PathFinding::getImage(const size_t index)
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
  img->sprite()->setRotation(static_cast<float> (angle));
  img->sprite()->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  // drawing at the middle of the cell
  img->sprite()->setPosition({
      static_cast<graphics::component> (_current.c) * p::cellWidth()
        + p::gridThickness() + p::gridOffsetX() + p::cellWidth()  / 2,
      static_cast<graphics::component> (_current.l) * p::cellHeight()
        + p::gridThickness() + p::gridOffsetY() + p::cellHeight() / 2});

  return img;
}

void PathFinding::addNextDirection(const e_direction direction)
{
  _directions.push_back(direction);
  ++_currentLength;
  highlightCells();
}


void PathFinding::highlightCells()
{
  _reachableCells.clear();
  _enemyPositions.clear();

  /// \todo check _unit's inventory
  //   (do not color enemies in red if we can't shoot them,
  //    color allies in a different color if we can heal them, ...)
  for (auto i(0u); i < _map->nbColumns(); ++i)
  {
    for (auto j(0u); j < _map->nbLines(); ++j)
    {
      auto c = (*_map)[i][j];

      // reset highlight for every cell
      c->setHighlight(false);

      // Compute manhattan distance of unit to every cell
      auto distance(manhattan(c->coords(), _current));

      // Skip out of range cells
      if (distance > _unit->motionValue() + _unit->maxRange() - _currentLength)
      {
        continue;
      }

      // Highlight reachable cells, depending on content, if any
      auto u = c->unit();
      if (distance <= _unit->motionValue() - _currentLength)
      {
        c->setHighlight(true);

        // empty cell, highlight as reachable
        if (!u)
        {
          _reachableCells.push_back((*_map)[i][j]);
          c->setHighlightColor(graphics::Color::Yellow);
          continue;
        }

        if (u->playerId() == Status::player()->id())
        {
          _reachableCells.push_back((*_map)[i][j]);
          c->setHighlightColor(graphics::Color::Green);
        }
        else
        {
          c->setHighlightColor(graphics::Color::Red);
          _enemyPositions.push_back(c);
        }

        continue;
      }

      // cells only at shooting range
      if (u && distance <= _unit->maxRange())
      {
        // unit out of moving range but at shooting range
        if (u->playerId() != Status::player()->id())
        {
          c->setHighlight(true);
          c->setHighlightColor(graphics::Color::Red);
          _enemyPositions.push_back(c);
        }
      }
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


bool PathFinding::allowedMove(e_direction direction)
{
  // If we reached the maximal length, the move won't be allowed
  if (_currentLength >= _maxLength)
  {
    return false;
  }

  // Getting destination cell
  std::shared_ptr<Cell> dst = nullptr;
  switch (direction)
  {
    case e_direction::UP:
      dst = _map->cell(Coords(_current.c, _current.l - 1));
      break;

    case e_direction::DOWN:
      dst = _map->cell(Coords(_current.c, _current.l + 1));
      break;

    case e_direction::LEFT:
      dst = _map->cell(Coords(_current.c - 1, _current.l));
      break;

    case e_direction::RIGHT:
      dst = _map->cell(Coords(_current.c + 1, _current.l));
      break;

    default:
      assert(!"Invalid direction");
      return false;
  }

  // do not allow to move over enemy units
  auto u(dst->unit());
  if (u && u->playerId() != Status::player()->id())
  {
    return false;
  }

  return true;
}



std::shared_ptr<std::vector<std::shared_ptr<Cell>>>
PathFinding::getTargets(const std::shared_ptr<Unit> unit,
                        const std::shared_ptr<Cell> cell)
{
  assert(unit && cell);

  highlightCells(); // update _enemyPositions if required

  std::vector<std::shared_ptr<Cell>> targets_list;
  for (const auto c: _enemyPositions)
  {
    auto distance(manhattan(c->coords(), cell->coords()));
    if (distance >= unit->minRange() && distance <= unit->maxRange())
    {
      targets_list.push_back(c);
    }
  }

  return std::make_shared<std::vector<std::shared_ptr<Cell>>> (targets_list);
}


size_t PathFinding::manhattan(const Coords a, const Coords b)
{
  // implicit cast into signed int
  int dist_columns(static_cast<int> (a.c - b.c));
  int dist_lines(  static_cast<int> (a.l - b.l));

  return std::abs(dist_columns) + std::abs(dist_lines);
}
