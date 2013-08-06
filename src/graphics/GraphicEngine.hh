/*
 * graphics/GraphicEngine.hh
 *
 *  Created on: April 15, 2013
 *      Author: Zermingore
 */

#ifndef GRAPHICENGINE_HH_
# define GRAPHICENGINE_HH_

# include <common/include.hh>
# include <common/Settings.hh>
# include <common/Status.hh>
# include <resources/ResourcesManager.hh>
# include <common/enums/units.hh>
# include <common/enums/terrains.hh>
# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <interface/menus/InGameMenu.hh>
# include <game/PathFinding.hh>


// TODO refresh only needed cells (mouse motion, cursor animation)

/** \brief Graphic Engine class
 ** manages the display of a scene
 */
class GraphicEngine
{
public:
  /** \brief Default Constructor
   */
  GraphicEngine();

  /** \brief Destructor
   */
  ~GraphicEngine();

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

  /// in case there are too many cells to display
  void drawGrid();

  /** \brief draws the grid (map cells delimiter)
   */
  void drawGrid(unsigned int nb_line, unsigned int nb_column);
};

#endif /* !GRAPHICENGINE_HH_ */
