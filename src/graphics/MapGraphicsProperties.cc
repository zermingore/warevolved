/**
 * \file
 * \date February 10, 2017
 * \author Zermingore
 * \namespace graphics
 * \brief MapGraphicsProperties class definition
 */

#include <graphics/MapGraphicsProperties.hh>


namespace graphics {


// Static class attributes definition
component MapGraphicsProperties::_cellWidth;
component MapGraphicsProperties::_cellHeight;
component MapGraphicsProperties::_gridThickness;
component MapGraphicsProperties::_gridOffsetX;
component MapGraphicsProperties::_gridOffsetY;


void MapGraphicsProperties::initialize()
{
  _cellWidth     = 64;
  _cellHeight    = 64;
  _gridThickness = 5;
  _gridOffsetX   = 0;
  _gridOffsetY   = 0;
}



} // namespace graphics
