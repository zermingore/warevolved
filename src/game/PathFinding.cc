#include "PathFinding.hh"
#include <common/macros.hh>
#include <common/globals.hh>


PathFinding::PathFinding() {
}

PathFinding::~PathFinding() {
}


void PathFinding::drawPath()
{
  _graphicPath.clear();
//  _graphicPath.push_back(E_PATH_SHAPE_UP);
  _graphicPath.push_back(E_PATH_SHAPE_RIGHT);

  unsigned int i = 5;
  for (auto it = _graphicPath.begin(); it != _graphicPath.end(); ++it)
  {
    this->getImage(*it)->drawAtCell(i, i);
    ++i;
  }
}


Image *PathFinding::getImage(e_path_shape shape)
{
  Image *img; // TODO use a copy Ctor (avoid rotating all sprites)
  unsigned int angle = 0;

  switch (shape)
  {
     // Arrows
     case E_PATH_SHAPE_LAST_UP:
     case E_PATH_SHAPE_LAST_DOWN:
     case E_PATH_SHAPE_LAST_LEFT:
     case E_PATH_SHAPE_LAST_RIGHT:
       img = GETIMAGE("soldiers");
       break;

     // Rectangles
     case E_PATH_SHAPE_UP:
     case E_PATH_SHAPE_DOWN:
     case E_PATH_SHAPE_LEFT:
     case E_PATH_SHAPE_RIGHT:
       img = GETIMAGE("soldiers");
       break;

     // Corners
     default:
       img = GETIMAGE("soldiers");
       break;
  }

  if ((angle = (unsigned int) shape % 360))
    img->getSprite()->setRotation(angle);

  return img;
}
