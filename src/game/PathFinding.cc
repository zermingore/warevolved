#include <game/PathFinding.hh>
#include <common/macros.hh>
#include <common/globals.hh>

PathFinding::PathFinding() :
  _cached (false),
  _maxLength (0),
  _currentLength (0)
{
}

PathFinding::~PathFinding() {
  this->deleteImagesVector();
}


void PathFinding::setOrigin(Coords coords)
{
  this->clearPath();

  _origin = coords;
  _current = coords;

  _cached = false;

  _currentLength = 0;
  _maxLength = g_status->getMap()->getUnit(coords)->getMotionValue();
}

unsigned int PathFinding::getCurrentLength() {
  return _currentLength;
}

void PathFinding::setCurrentLength(const unsigned int length) {
  _currentLength = length;
}

unsigned int PathFinding::getMaxLength() {
  return _maxLength;
}

void PathFinding::setMaxLength(const unsigned int length) {
  _maxLength = length;
}


void PathFinding::drawPath()
{
//  if (!_cached)
//    buildImageVector();

  _current = _origin;
  unsigned int i = 0;
  for (auto it = _directions.begin(); it != _directions.end(); ++it)
  {
    this->updateCurrentCell(*it);
    // TODO manage cache and image sprites
    // _images[i++]->drawAtCell(_currentX, _currentY);
    this->getImage(i++)->drawAtCell(_current);
  }

//  _cached = false;
}


void PathFinding::clearPath()
{
  _directions.clear();
  this->deleteImagesVector();
  //_cached = false;

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


void PathFinding::deleteImagesVector()
{
  // freeing images
  for (auto it = _images.begin(); it != _images.end(); ++it)
  {
    if (*it)
      delete (*it);
  }

  _images.clear();
}


void PathFinding::buildImageVector()
{
  // manage 'riding' the path (increment a global index)
  // this->deleteImagesVector();

  unsigned int i = 0;
  for (auto it = _directions.begin(); it != _directions.end(); ++it)
    _images.push_back(this->getImage(i++));

  _cached = true;
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


Image *PathFinding::getImage(unsigned int index)
{
  Image *img; // TODO use a copy Ctor (avoid rotating all sprites)
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
  img->getSprite()->setRotation(angle);

  return img;
}

bool PathFinding::allowedMove() {
  return _currentLength < _maxLength;
}

void PathFinding::addNextDirection(e_direction direction)
{
  _directions.push_back(direction);
  ++_currentLength;

  // TODO add Image
}
