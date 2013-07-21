#include <game/PathElement.hh>
#include <game/PathFinding.hh>


PathElement::PathElement() :
  _x (0),
  _y (0),
  _shape (E_PATH_NONE)
{
}

PathElement::PathElement(unsigned int x, unsigned int y, e_path_shape shape) :
  _x (x),
  _y (y),
  _shape (shape)
{
}

PathElement::~PathElement() {
}


unsigned int PathElement::getX() {
  return _x;
}

unsigned int PathElement::getY() {
  return _y;
}
