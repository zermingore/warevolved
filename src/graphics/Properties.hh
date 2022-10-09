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
  ///< Map cells width in pixels
  inline static const component _cellWidth{64};

  ///< Map cells height in pixels
  inline static const component _cellHeight{64};

  ///< Inventory cell width in pixels
  inline static const component _inventoryCellWidth{_cellWidth / 4};

  ///< Inventory cell width in pixels
  inline static const component _inventoryCellHeight{_cellHeight / 4};

  ///< Thickness of the grid
  inline static const component _gridThickness{5};

  ///< X offset (from the window left border)
  inline static component _gridOffsetX{0};

  ///< Y offset (from the window top border)
  inline static component _gridOffsetY{0};
};


} // namespace graphics

#endif /* !GRAPHICS_PROPERTIES_HH_ */
