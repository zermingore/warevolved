/**
 * \file
 * \date February 10, 2017
 * \author Zermingore
 * \namespace graphics
 * \brief Properties class definition
 */

#include <graphics/Properties.hh>


namespace graphics {


// Static class attributes definition
component Properties::_cellWidth     = 64;
component Properties::_cellHeight    = 64;
component Properties::_gridThickness = 5;
component Properties::_gridOffsetX   = 0;
component Properties::_gridOffsetY   = 0;


component Properties::_inventoryCellWidth =
 Properties::_cellWidth / 4;

component Properties::_inventoryCellHeight =
 Properties::_cellHeight / 4;


} // namespace graphics
