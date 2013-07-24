#ifndef GRAPHICENGINE_HH_
# define GRAPHICENGINE_HH_

# include <common/include.hh>
# include <common/Settings.hh>
# include <common/Status.hh>
# include <resources/ResourcesManager.hh>
# include <common/units.hh>
# include <common/terrains.hh>
# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <interface/ActionMenu.hh>
# include <interface/SelectionMenu.hh>
# include <game/PathFinding.hh>


// TODO refresh only needed cells (mouse motion, cursor animation)

class GraphicEngine
{
public:
  /** \brief Default Constructor
   */
  GraphicEngine();

  /** \brief Destructor
   */
  ~GraphicEngine();

  /** \brief updates current path
   */
  void updatePath(PathFinding *p);

  /** \brief Draws the whole scene
   **   calls others drawing functions
   */
  void drawScene();


private:
  /** \brief Initializes drawable zone limits
   **   by setting g_status gridOffsets
   */
  void initRoom();

  /** \brief Draws the map background
   */
  void drawBackground();

  /** \brief Draw side panel
   */
  void drawPanel();

  /** \brief Draw menu bar
   */
  void drawMenuBar();

  /** \brief Draws cell content (terrain, unit)
   */
  void drawCells();

  /// in case there are too many cells to display
  void drawGrid();
  void drawGrid(unsigned int nb_line, unsigned int nb_column);

  /** \brief Draw map cursor
   */
  void drawCursor();

  /** \brief Draw Selection Menu
   ** selection menu pop when you select something
   **
   ** \param cell The Cell on which the cursor is
   */
  void drawSelectionMenu(Cell *cell);

  /** \brief Draw Selection Menu or Action menu
   ** selection menu pop when you select something
   ** fetches automatically cell on which the cursor is
   ** action menu pops at the end of a move (when 'stop' is selected)
   */
  void drawInGameMenus();

  /** \brief draws current path
   */
  void drawPath();


  // space left for rendering
  // unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  // unsigned int _renderY; ///< Drawable zone room left vertically (in px)

  unsigned int _IDTST; // rm

  Cursor *_cursor;
  SelectionMenu *_selectionMenu;
  ActionMenu *_actionMenu;
  PathFinding *_path;
};

#endif /* !GRAPHICENGINE_HH_ */
