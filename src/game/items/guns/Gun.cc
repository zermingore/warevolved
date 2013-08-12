#include <game/items/guns/Gun.hh>

Gun::Gun() :
  _range (1)
{
}

Gun::~Gun() {
}

unsigned int Gun::getRange() {
  return _range;
}
