#include <game/PathFinding.hh>
#include <common/macros.hh>
#include <common/globals.hh>


PathFinding::PathFinding() {
}

PathFinding::~PathFinding() {
}


void PathFinding::drawPath()
{
  // if cached
//  for (auto it = _graphicPath.begin(); it != _graphicPath.end(); ++it)
//    this->getImage(*it)->drawAtCell((*it)->getX(), (*it)->getY());

  // To display an element, we have to know it's predecessor and it's successor
  //   So let's manage some cases
  if (_directions.size() < 2 || _directions.size() < 3) // TODO manage short lists
    return;

  unsigned int i = 0;
  for (auto it = _directions.begin(); it != _directions.end() - 1; ++it)
    this->getImage(i++)->drawAtCell(_currentX, _currentY);

  // last element
}

void PathFinding::buildImageList()
{
  // manage 'riding' the path (move orgin cell, inc index)
  // if cached return

  // current x, y cell
  unsigned int x = _originX;
  unsigned int y = _originY;

    // To display an element, we have to know it's predecessor and it's successor
    //   So let's manage some cases
    if (_directions.size() < 2 || _directions.size() < 3) // TODO manage short lists
      return;

    unsigned int i = 0;
    for (auto it = _directions.begin(); it != _directions.end() - 1; ++it)
      this->getImage(i++)->drawAtCell(_currentX, _currentY);

    // last element
}


e_path_shape PathFinding::getShape(unsigned int index)
{
  // last element case
  if (index == _directions.size())
    return ((e_path_shape) (_directions[index] - 360));

  // same element as next case
  if (_directions[index] == _directions[index + 1])
    return ((e_path_shape) _directions[index]);

  // from here, we know the direction changed
  unsigned int offset = 0;
  switch (_directions[index + 1])
  {
    case E_DIRECTION_UP:
    case E_DIRECTION_LEFT:
      offset = 360;
      break;

    case E_DIRECTION_DOWN:
    case E_DIRECTION_RIGHT:
      offset = 720;
      break;

    default: // E_DIRECTION_NONE (could merge with previous cases)
      break;
  }

  return ((e_path_shape) (_directions[index] + offset));
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
       img = GETIMAGE("path_arrow");
       break;
  }

  if ((angle = (unsigned int) shape % 360))
    img->getSprite()->setRotation(angle);

  return img;
}


void PathFinding::addNextDirection(e_direction direction)
{
  _directions.push_back(direction);
}
