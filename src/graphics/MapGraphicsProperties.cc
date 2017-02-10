#include <graphics/MapGraphicsProperties.hh>


#include <debug/Debug.hh>


namespace graphics {


// Static class attributes definition
size_t MapGraphicsProperties::_cellWidth;
size_t MapGraphicsProperties::_cellHeight;
size_t MapGraphicsProperties::_gridThickness;
size_t MapGraphicsProperties::_gridOffsetX;
size_t MapGraphicsProperties::_gridOffsetY;


void MapGraphicsProperties::initialize()
{
  _cellWidth     = 64;
  _cellHeight    = 64;
  _gridThickness = 5;
  _gridOffsetX   = 0;
  _gridOffsetY   = 0;
}



} // namespace graphics
