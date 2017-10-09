#include <game/PathFinding.hh>

#include <debug/Debug.hh>

#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Map.hh>
#include <game/Cell.hh>
#include <game/units/Unit.hh>
#include <game/Status.hh>
#include <common/enums/directions.hh>
#include <common/enums/path_shapes.hh>
#include <graphics/Sprite.hh>
#include <graphics/graphic_types.hh>
#include <graphics/MapGraphicsProperties.hh>



PathFinding::PathFinding(std::shared_ptr<Unit> origin)
  : _currentLength(0)
{
  _origin = origin;
  _current = origin->coords();
  _maxLength = origin->motionValue();

  _map = game::Status::battle()->map();
}


PathFinding::~PathFinding()
{
  clearPath();
}


void PathFinding::drawPath()
{
  _lastPosition = _current;
//  PRINTF("_current in drawPath():", _lastPosition);
  _current = _origin->coords();

  size_t i = 0;
  for (auto it(_directions.begin()); it != _directions.end(); ++it)
  {
    updateCurrentCell(*it);
    getSprite(i++)->draw(); /// \todo drawAtCell
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
    _images.push_back(getSprite(i));
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
  if (std::abs(static_cast<int> (_directions[index]) - static_cast<int> (next))
      == 180)
  {
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


std::shared_ptr<graphics::Sprite> PathFinding::getSprite(const size_t index)
{
  std::shared_ptr<graphics::Sprite> img;
  e_path_shape shape = getShape(index);

  switch (shape)
  {
     // Rectangles
     case e_path_shape::UP:
     case e_path_shape::DOWN:
     case e_path_shape::LEFT:
     case e_path_shape::RIGHT:
       img = std::make_shared<graphics::Sprite> ("path_shape");
       break;

     // Arrows
     case e_path_shape::LAST_UP:
     case e_path_shape::LAST_DOWN:
     case e_path_shape::LAST_LEFT:
     case e_path_shape::LAST_RIGHT:
       img = std::make_shared<graphics::Sprite> ("path_arrow");
       break;

     // Corners
     default:
       img = std::make_shared<graphics::Sprite> ("path_corner");
       break;
  }

  using p = graphics::MapGraphicsProperties;

  unsigned int angle(static_cast<int> (shape) % 360);
  img->setRotation(static_cast<float> (angle));
  img->setOrigin(p::cellWidth() / 2, p::cellHeight() / 2);

  // drawing at the middle of the cell
  img->setPosition(
      static_cast<graphics::component> (_current.c) * p::cellWidth()
        + p::gridThickness() + p::gridOffsetX() + p::cellWidth()  / 2,
      static_cast<graphics::component> (_current.l) * p::cellHeight()
        + p::gridThickness() + p::gridOffsetY() + p::cellHeight() / 2);

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

  /// \todo check unit's inventory
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
      if (distance
          > _origin->motionValue() + _origin->maxRange() - _currentLength)
      {
        continue;
      }

      // Highlight reachable cells, depending on content, if any
      auto u = c->unit();
      if (distance <= _origin->motionValue() - _currentLength)
      {
        c->setHighlight(true);

        // empty cell, highlight as reachable
        if (!u)
        {
          _reachableCells.push_back((*_map)[i][j]);
          c->setHighlightColor(graphics::Color::Yellow);
          continue;
        }

        if (u->playerId() == game::Status::player()->id())
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
      if (u && distance <= _origin->maxRange())
      {
        // unit out of moving range but at shooting range
        if (u->playerId() != game::Status::player()->id())
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
  if (u && u->playerId() != game::Status::player()->id())
  {
    return false;
  }

  return true;
}



std::shared_ptr<std::vector<std::shared_ptr<Cell>>>
PathFinding::getTargets(Coords coords)
{
  highlightCells(); // update _enemyPosition

  std::vector<std::shared_ptr<Cell>> targets_list;
  for (const auto c: _enemyPositions)
  {
    auto distance(manhattan(c->coords(), coords));
    if (distance >= _origin->minRange() && distance <= _origin->maxRange())
    {
      targets_list.push_back(c);
    }
  }

  PRINTF("Path finding: found", targets_list.size(), "targets from:", coords);

  return std::make_shared<std::vector<std::shared_ptr<Cell>>> (targets_list);
}



size_t PathFinding::manhattan(const Coords a, const Coords b)
{
  // explicit cast into signed int
  int dist_columns(static_cast<int> (a.c - b.c));
  int dist_lines(  static_cast<int> (a.l - b.l));

  return std::abs(dist_columns) + std::abs(dist_lines);
}
