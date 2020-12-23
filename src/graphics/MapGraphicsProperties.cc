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
component MapGraphicsProperties::_cellWidth     = 64;
component MapGraphicsProperties::_cellHeight    = 64;
component MapGraphicsProperties::_gridThickness = 5;
component MapGraphicsProperties::_gridOffsetX   = 0;
component MapGraphicsProperties::_gridOffsetY   = 0;


component MapGraphicsProperties::_inventoryCellWidth =
 MapGraphicsProperties::_cellWidth / 4;

component MapGraphicsProperties::_inventoryCellHeight =
 MapGraphicsProperties::_cellHeight / 4;


} // namespace graphics
