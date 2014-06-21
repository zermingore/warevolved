/*
 * graphics/GraphicsEngine.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GRAPHICSENGINE_HH_
# define GRAPHICSENGINE_HH_


/** \brief Graphics Engine class
 ** manages the display of a scene
 */
class GraphicsEngine
{
public:
  /** \brief Draws the whole scene
   **   calls others drawing functions
   */
  void drawScene();

  /** \brief Initializes drawable zone limits
   **   by setting g_status gridOffsets
   */
  void initRoom();


private:
  /** \brief Draws the map background
   */
  void drawBackground();

  /** \brief Draws cell content (terrain, unit)
   */
  void drawCells();

  /// \brief in case there are too many cells to display
  void drawGrid();
};

#endif /* !GRAPHICSENGINE_HH_ */
