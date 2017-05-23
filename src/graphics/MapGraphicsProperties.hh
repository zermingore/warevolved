/**
 * \file
 * \date February 10, 2017
 * \author Zermingore
 * \brief Map class definition.
 */

#ifndef MAP_GRAPHICS_PROPERTIES_HH_
# define MAP_GRAPHICS_PROPERTIES_HH_


namespace graphics {

/**
 * \class MapGraphicsProperties
 * \brief Graphics properties of the Map (cell sizes, grid thickness, ...)
 */
class MapGraphicsProperties
{
public:
  /**
   * \brief Initialize attributes with default values.
   */
  static void initialize();

  /**
   * \brief cell width getter.
   * \return cell width in pixels.
   */
  static auto cellWidth() { return _cellWidth; }

  /**
   * \brief cell height getter.
   * \return cell height in pixels.
   */
  static auto cellHeight() { return _cellHeight; }

  /**
   * \brief grid thickness getter.
   * \return grid thickness in pixels.
   */
  static auto gridThickness() { return _gridThickness; }

  /**
   * \brief offset of the grid (from the left border of the window) getter.
   * \return grid offset, in x.
   */
  static auto gridOffsetX() { return _gridOffsetX; }

  /**
   * \brief offset of the grid (from the top border of the window) getter.
   * \return grid offset, in y.
   */
  static auto gridOffsetY() { return _gridOffsetY; }

  /**
   * \brief cell width setter.
   * \param width cell width in pixels.
   */
  static void setCellWidth(float width) { _cellWidth = width; }

  /**
   * \brief cell height setter.
   * \param height cell height in pixels.
   */
  static void setCellHeight(float height) { _cellHeight = height; }

  /**
   * \brief grid thickness setter.
   * \param thickness of the grid in pixels.
   */
  static void setGridThickness(float thickness) { _gridThickness = thickness; }

  /**
   * \brief offset of the grid (from the left border of the window) setter.
   * \param x offset.
   */
  static void setGridOffsetX(float grid_offset_x) { _gridOffsetX = grid_offset_x; }

  /**
   * \brief offset of the grid (from the top border of the window) setter.
   * \param y offset.
   */
  static void setGridOffsetY(float grid_offset_y) { _gridOffsetY = grid_offset_y; }


private:
  static float _cellWidth;     ///< cells width in pixels
  static float _cellHeight;    ///< cells height in pixels
  static float _gridThickness; ///< thickness of the grid
  static float _gridOffsetX;   ///< X grid offset (from the window left border)
  static float _gridOffsetY;   ///< Y grid offset (from the window top border)
};


} // namespace graphics

#endif /* !MAP_GRAPHICS_PROPERTIES_HH_ */
