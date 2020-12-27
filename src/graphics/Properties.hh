/**
 * \file
 * \date February 10, 2017
 * \author Zermingore
 * \namespace graphics
 * \brief Properties class declaration
 */

#ifndef GRAPHICS_PROPERTIES_HH_
# define GRAPHICS_PROPERTIES_HH_

# include <graphics/graphic_types.hh>



namespace graphics {


/**
 * \class Properties
 * \brief Graphics properties of the Map (cell sizes, grid thickness, ...)
 */
class Properties
{
public:
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
   * \brief Cell width getter.
   * \return Cell width in pixels.
   */
  static auto inventoryCellWidth() { return _inventoryCellWidth; }

  /**
   * \brief Cell height getter.
   * \return Cell height in pixels.
   */
  static auto inventoryCellHeight() { return _inventoryCellHeight; }

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
  static void setCellWidth(component width) { _cellWidth = width; }

  /**
   * \brief cell height setter.
   * \param height cell height in pixels.
   */
  static void setCellHeight(component height) { _cellHeight = height; }

  /**
   * \brief grid thickness setter.
   * \param thickness of the grid in pixels.
   */
  static void setGridThickness(component thickness) {
    _gridThickness = thickness;
  }

  /**
   * \brief offset of the grid (from the left border of the window) setter.
   * \param grid_offset_x offset.
   */
  static void setGridOffsetX(component grid_offset_x) {
    _gridOffsetX = grid_offset_x;
  }

  /**
   * \brief offset of the grid (from the top border of the window) setter.
   * \param grid_offset_y offset.
   */
  static void setGridOffsetY(component grid_offset_y) {
    _gridOffsetY = grid_offset_y;
  }


private:
  /// \todo These are not const because they will be modifyable later
  static component _cellWidth;     ///< Map cells width in pixels
  static component _cellHeight;    ///< Map cells height in pixels
  static component _gridThickness; ///< Thickness of the grid
  static component _gridOffsetX;   ///< X offset (from the window left border)
  static component _gridOffsetY;   ///< Y offset (from the window top border)

  static component _inventoryCellWidth;  ///< Inventory cell width in pixels
  static component _inventoryCellHeight; ///< Inventory cell width in pixels
};


} // namespace graphics

#endif /* !GRAPHICS_PROPERTIES_HH_ */
