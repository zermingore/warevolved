#include <game/Cell.hh>
#include <common/enums/terrains.hh>


Cell::Cell(const size_t c, const size_t l) :
  _terrain(e_terrain::NONE),
  _unit(nullptr),
  _highlight(false),
  _highlightColor(255, 255, 255)
{
  _coords.c = c;
  _coords.l = l;
}
