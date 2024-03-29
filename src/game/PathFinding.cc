/**
 * \file
 * \date July 18, 2013
 * \author Zermingore
 * \brief PathFinding class definition
 */

#include <game/PathFinding.hh>

#include <exception>
#include <stack>

#include <debug/Debug.hh>
#include <debug/OSD.hh>

#include <game/Battle.hh>
#include <game/Cell.hh>
#include <game/Map.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/Terrain.hh>
#include <game/TerrainsHandler.hh>
#include <game/units/Unit.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <graphics/graphic_types.hh>



PathFinding::PathFinding(const std::shared_ptr<Unit>& origin)
  : _maxLength(0)
  , _currentLength(0)
{
  if (!origin)
  {
    throw std::exception();
  }

  _origin = origin;
  _current = origin->coords();
  _maxLength = origin->motionValue();
  _map = game::Status::battle()->map();

  // Setting the cost to every cell to infinity
  const auto out_of_reach(_origin->maxRange() + _origin->motionValue() + 1);
  const auto cells(_map->cells());
  for (auto col(0u); col < _map->nbColumns(); ++col)
  {
    std::vector<size_t> vec(_map->nbLines(), out_of_reach);
    for (auto line(0u); line < _map->nbLines(); ++line)
    {
      _costs.emplace_back(vec);
    }
  }

  computeCosts();
}



void PathFinding::drawPath()
{
  _lastPosition = _current;
  _current = _origin->coords();

  // Locking as addDirection() may invalidate the end iterator concurrently
  // It is safe to access elements concurrently only if there is no relocation
  auto i(0u);
  _lockDirections.lock();
  for (const auto it: _directions)
  {
    updateCurrentCell(it);
    getSprite(i++)->draw(); /// \todo drawAtCell
  }
  _lockDirections.unlock();
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
      break;
  }
}



e_path_shape PathFinding::getShape(size_t index) const
{
  assert(index < _directions.size());

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

  using p = graphics::Properties;

  unsigned int angle(static_cast<unsigned int> (shape) % 360);
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



void PathFinding::addNextDirection(const e_direction direction,
                                   const Coords& coords)
{
  _lockDirections.lock();
  _directions.emplace_back(direction);
  _lockDirections.unlock();

  _currentLength += TerrainsHandler::cost(
    (*_map)[coords.c][coords.l]->terrain(), _origin->type());
  highlightCells();
}



void PathFinding::computeCosts()
{
  const auto nb_col(_map->nbColumns());
  const auto nb_lines(_map->nbLines());

  _costs[_origin->coords().c][_origin->coords().l] = 0;
  std::stack<std::pair<int, int>> candidates;
  candidates.push({ _origin->coords().c, _origin->coords().l });
  while (!candidates.empty())
  {
    const auto col =  static_cast<size_t> (candidates.top().first);
    const auto line = static_cast<size_t> (candidates.top().second);
    candidates.pop();

    // Skipping cells containing enemy units as we cannot cross them
    auto c = (*_map)[col][line];
    if (c->unit() && c->unit()->playerId() != game::Status::player()->id()) {
      continue;
    }

    // Considering adjacent Cells and minimizing their distance
    const auto type{_origin->type()};
    auto cells{_map->cells()};
    const auto distance = _costs[col][line];
    if (col > 0)
    {
      const auto costCurrentCell {
        TerrainsHandler::cost(cells[col - 1][line]->terrain(), type) };
      if ( distance + costCurrentCell < _costs[col - 1][line])
      {
        _costs[col - 1][line] = distance + costCurrentCell;
        candidates.emplace(col - 1, line);
      }
    }

    if (col < nb_col - 1)
    {
      const auto costCurrentCell {
        TerrainsHandler::cost(cells[col + 1][line]->terrain(), type) };
      if (distance + costCurrentCell < _costs[col + 1][line])
      {
        _costs[col + 1][line] = distance + costCurrentCell;
        candidates.emplace(col + 1, line);
      }
    }

    if (line > 0)
    {
      const auto costCurrentCell {
        TerrainsHandler::cost(cells[col][line - 1]->terrain(), type) };
      if (distance + costCurrentCell < _costs[col][line - 1])
      {
        _costs[col][line - 1] = distance + costCurrentCell;
        candidates.emplace(col, line - 1);
      }
    }

    if (line < nb_lines - 1)
    {
      const auto costCurrentCell {
        TerrainsHandler::cost(cells[col][line + 1]->terrain(), type) };
      if (distance + costCurrentCell < _costs[col][line + 1])
      {
        _costs[col][line + 1] = distance + costCurrentCell;
        candidates.emplace(col, line + 1);
      }
    }
  }
}



void PathFinding::highlightCells()
{
  const auto nb_col(_map->nbColumns());
  const auto nb_lines(_map->nbLines());
  const auto out_of_reach(_origin->maxRange() + _origin->motionValue() + 1);

  // Highlight reachable cells
  for (auto c(0ul); c < nb_col; ++c)
  {
    for (auto l(0ul); l < nb_lines; ++l)
    {
      // Skipping unreachable cells
      if (_costs[c][l] >= out_of_reach) {
        continue;
      }

      debug::OSD::writeOnCell(c, l, std::to_string(_costs[c][l]));

      // Highlight only reachable cells
      auto cell = (*_map)[c][l];
      auto unit = cell->unit();
      if (_costs[c][l] <= _origin->motionValue())
      {
        cell->setHighlight(true);
        cell->setHighlightColor(graphics::Color::Yellow);

        // Own units
        if (unit && unit->playerId() == game::Status::player()->id())
        {
          cell->setHighlightColor(graphics::Color::Green);
          continue; // there can be only one unit per cell
        }
      }

      // Highlight reachable enemies (taking into account the Unit range)
      if (unit && unit->playerId() != game::Status::player()->id())
      {
        cell->setHighlight(true);
        cell->setHighlightColor(graphics::Color::Red);
      }
    }
  }

  // Do not highlight the origin Cell nor the holo unit cell
  _map->cell(_origin->coords())->setHighlight(false);
}



void PathFinding::hideAllowedPath()
{
  _map->clearHighlights();
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
      assert(false && "Invalid direction");
      return false;
  }

  // Take destination terrain motion cost into account
  if (_currentLength + TerrainsHandler::cost(dst->terrain(), _origin->type())
    > _maxLength)
  {
    return false;
  }

  // Do not allow to move over enemy units
  auto u{dst->unit()};
  return !u || u->playerId() == game::Status::player()->id();
}



std::shared_ptr<std::vector<std::shared_ptr<const Cell>>>
PathFinding::getTargets(
  const std::shared_ptr<const Unit>& ref, const Coords& coords) const
{
  // Dummy: for every cell if unit && not one of the current player -> target
  // (NOT considering the motion value)
  std::vector<std::shared_ptr<const Cell>> targets;

  for (auto i(0u); i < _map->nbColumns(); ++i)
  {
    for (auto j(0u); j < _map->nbLines(); ++j)
    {
      const auto c = (*_map)[i][j];
      const auto unit = c->unit();
      if (unit
          && unit->playerId() != game::Status::player()->id()
          && manhattan(c->coords(), coords) <= ref->maxRange())
      {
        targets.emplace_back(c);
      }
    }
  }

  return std::make_shared<std::vector<std::shared_ptr<const Cell>>> (targets);
}



std::vector<std::shared_ptr<const Cell>>
PathFinding::getAdjacentCells(const Coords coords) const
{
  std::vector<std::shared_ptr<const Cell>> adjacents; // return value

  const auto nb_col(_map->nbColumns());
  const auto nb_lines(_map->nbLines());

  if (coords.c > 0)
  {
    adjacents.emplace_back((*_map)[coords.c - 1][coords.l]);
  }

  if (coords.c < nb_col - 1)
  {
    adjacents.emplace_back((*_map)[coords.c + 1][coords.l]);
  }

  if (coords.l > 0)
  {
    adjacents.emplace_back((*_map)[coords.c][coords.l - 1]);
  }

  if (coords.l < nb_lines - 1)
  {
    adjacents.emplace_back((*_map)[coords.c][coords.l + 1]);
  }

  return adjacents;
}



std::vector<std::shared_ptr<const Cell>>
PathFinding::getDropZones(const Coords& coords) const
{
  auto candidates = getAdjacentCells(coords);

  // return value initialization
  std::vector<std::shared_ptr<const Cell>> dropZones(candidates.size());

  auto it = std::copy_if(
    candidates.begin(),
    candidates.end(),
    dropZones.begin(),
    [] (std::shared_ptr<const Cell> c) {
      return !c->unit() && (   c->terrain() == e_terrain::BUILDING_DOOR
                            || c->terrain() == e_terrain::FOREST
                            || c->terrain() == e_terrain::PLAIN);
    }
  );

  // shrink container to new size (necessary to drop invalid items)
  dropZones.resize(static_cast<size_t> (std::distance(dropZones.begin(), it)));

  return dropZones;
}



size_t PathFinding::manhattan(const Coords a, const Coords b) const
{
  // explicit cast into signed int
  int dist_columns(static_cast<int> (a.c - b.c));
  int dist_lines(  static_cast<int> (a.l - b.l));

  return static_cast<size_t> (std::abs(dist_columns) + std::abs(dist_lines));
}
