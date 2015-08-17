/*
 * graphics/Mapgraphicsproperties.hh
 *
 *  Created on: July 24, 2015
 *      Author: Zermingore
 */

#ifndef MAPGRAPHICSPROPERTIES_HH_
# define MAPGRAPHICSPROPERTIES_HH_

class MapGraphicsProperties
{
public:
  MapGraphicsProperties();

  inline unsigned int cellWidth() { return _cellWidth; }
  inline unsigned int cellHeight() { return _cellHeight; }
  inline unsigned int gridThickness() { return _gridThickness; }
  inline unsigned int gridOffsetX() { return _gridOffsetX; }
  inline unsigned int gridOffsetY() { return _gridOffsetY; }


  inline void setCellWidth(unsigned int cell_width) { _cellWidth = cell_width; }
  inline void setCellHeight(unsigned int cell_height) { _cellHeight = cell_height; }
  inline void setGridThickness(unsigned int grid_thickness) { _gridThickness = grid_thickness; }
  inline void setGridOffsetX(unsigned int grid_offset_x) { _gridOffsetX = grid_offset_x; }
  inline void setGridOffsetY(unsigned int grid_offset_y) { _gridOffsetY = grid_offset_y; }

private:
  unsigned int _cellWidth; ///< cells width
  unsigned int _cellHeight; ///< cells height
  unsigned int _gridThickness; ///< thickness of the grid
  unsigned int _gridOffsetX; ///< X offset of the grid (related to the window)
  unsigned int _gridOffsetY; ///< Y offset of the grid (related to the window)
};

#endif /* !MAPGRAPHICSPROPERTIES_HH_ */
