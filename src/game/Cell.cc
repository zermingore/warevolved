/**
 * \file
 * \date April 19, 2013
 * \author Zermingore
 * \brief Cell class definition
 */

#include <common/enums/terrains.hh>
#include <game/Cell.hh>


Cell::Cell(size_t c, size_t l, e_terrain terrain)
  : _terrain(terrain)
  , _unit(nullptr)
  , _highlight(false)
  , _highlightColor(255, 255, 255)
{
  _coords.c = c;
  _coords.l = l;
}
