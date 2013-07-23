#include <game/PathFinding.hh>
#include <common/macros.hh>
#include <common/globals.hh>

PathFinding::PathFinding() :
  _originX (0),
  _originY (0),
  _currentX (0),
  _currentY (0)
{
}

PathFinding::~PathFinding() {
  this->deleteImagesVector();
}


void PathFinding::setOrigin(unsigned int x, unsigned int y)
{
  this->clearPath();

  _originX = x;
  _originY = y;

  _currentX = x;
  _currentY = y;
}


void PathFinding::drawPath()
{
  // TODO cache management
  //  unsigned int i = 0;
  //  for (auto it = _directions.begin(); it != _directions.end(); ++it)
  //  {
  //    _images[i++]->drawAtCell(_currentX, _currentY);
  //    this->updateCurrentCell(*it);
  //  }
  //  return;

  _currentX = _originX;
  _currentY = _originY;

  unsigned int i = 0;
  for (auto it = _directions.begin(); it != _directions.end(); ++it)
  {
    this->updateCurrentCell(*it);
    this->getImage(i++)->drawAtCell(_currentX, _currentY);
  }
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
      --_currentY;
      return;

    case E_DIRECTION_DOWN:
      ++_currentY;
      return;

    case E_DIRECTION_LEFT:
      --_currentX;
      return;

    case E_DIRECTION_RIGHT:
      ++_currentX;
      return;

    default:
      return;
  }
}


void PathFinding::deleteImagesVector()
{
  // freeing images
  for (auto it = _images.begin(); it != _images.end(); ++it)
    delete (*it);

  _images.clear();
}


// unused
//void PathFinding::buildImageVector()
//{
//  // manage 'riding' the path (inc a global index)
//  // if cached return
//
//  this->deleteImagesVector();
//
//  unsigned int i = 0;
//  for (auto it = _directions.begin(); it != _directions.end(); ++it)
//    _images.push_back(this->getImage(i++));
//}


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

//  DEBUG_PRINT_VALUE(_directions[index]);

  // from here, we know the direction changed
  unsigned int offset = 720; // e_path_shape offset
  if (next == E_DIRECTION_DOWN || next == E_DIRECTION_RIGHT)
    offset = 360;

//  if (std::abs(next - _directions[index]) == 90)
  if (_directions[index] == E_DIRECTION_RIGHT && next == E_DIRECTION_UP) // 180
    return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_LEFT_UP)); // 270

  if (_directions[index] == E_DIRECTION_UP && next == E_DIRECTION_LEFT) // 270
    return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_DOWN_LEFT)); // 180

  if (_directions[index] == E_DIRECTION_LEFT && next == E_DIRECTION_DOWN) // 90
    return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_RIGHT_DOWN)); // 90

  if (_directions[index] == E_DIRECTION_DOWN && next == E_DIRECTION_RIGHT) // 90
    return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_UP_RIGHT)); // 0


  // anti clockwise
  if (_directions[index] == E_DIRECTION_LEFT && next == E_DIRECTION_UP)
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_RIGHT_UP));

  if (_directions[index] == E_DIRECTION_UP && next == E_DIRECTION_RIGHT)
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_DOWN_RIGHT));

  if (_directions[index] == E_DIRECTION_RIGHT && next == E_DIRECTION_DOWN)
      return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_LEFT_DOWN));

  // down left
  return (static_cast <e_path_shape> (E_PATH_SHAPE_CORNER_UP_LEFT));
}


Image *PathFinding::getImage(unsigned int index)
{
  Image *img; // TODO use a copy Ctor (avoid rotating all sprites)
  unsigned int angle = 0;
  e_path_shape shape = getShape(index);

//  DEBUG_PRINT_VALUE(shape);

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
       DEBUG_PRINT_VALUE(shape);
       break;
  }

  angle = static_cast <unsigned int> (shape % 360);
  img->getSprite()->setRotation(angle); // -90

  return img;
}


void PathFinding::addNextDirection(e_direction direction)
{
  _directions.push_back(direction);

  // TODO add Image
}
