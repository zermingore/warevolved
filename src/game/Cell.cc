#include <game/Cell.hh>
#include <common/enums/terrains.hh>


Cell::Cell(size_t x, size_t y) :
  _terrain (e_terrain::NONE),
  _unit (nullptr),
  _highlight (false),
  _highlightColor (255, 255, 255)
{
  _coords.x = x;
  _coords.y = y;
}
