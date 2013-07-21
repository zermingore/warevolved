#include <game/PathFinding.hh>
#include <common/macros.hh>
#include <common/globals.hh>


PathFinding::PathFinding() {
}

PathFinding::~PathFinding() {
}


void PathFinding::drawPath()
{
  _graphicPath.clear();
  PathElement p (1,1, E_PATH_SHAPE_LEFT);
  _graphicPath.push_back(&p);

  PathElement p2 (1,2, E_PATH_SHAPE_LAST_DOWN);
  _graphicPath.push_back(&p2);

  for (auto it = _graphicPath.begin(); it != _graphicPath.end(); ++it)
    this->getImage((*it)->getShape())->drawAtCell((*it)->getX(), (*it)->getY());
}


Image *PathFinding::getImage(e_path_shape shape)
{
  Image *img; // TODO use a copy Ctor (avoid rotating all sprites)
  unsigned int angle = 0;

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
