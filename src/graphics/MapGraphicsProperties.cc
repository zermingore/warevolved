#include <graphics/MapGraphicsProperties.hh>


namespace graphics {


// Static class attributes definition
float MapGraphicsProperties::_cellWidth;
float MapGraphicsProperties::_cellHeight;
float MapGraphicsProperties::_gridThickness;
float MapGraphicsProperties::_gridOffsetX;
float MapGraphicsProperties::_gridOffsetY;


void MapGraphicsProperties::initialize()
{
  _cellWidth     = 64;
  _cellHeight    = 64;
  _gridThickness = 5;
  _gridOffsetX   = 0;
  _gridOffsetY   = 0;
}



} // namespace graphics
