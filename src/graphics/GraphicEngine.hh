#ifndef GRAPHICENGINE_HH_
# define GRAPHICENGINE_HH_

# include <common/include.hh>
# include <common/Settings.hh>
# include <common/Status.hh>
# include <common/units.hh>
# include <common/terrains.hh>
# include <common/interface.hh>
# include <game/Map.hh>


class GraphicEngine
{
public:
  /** \brief Default Constructor
   */
  GraphicEngine();
  GraphicEngine(sf::RenderWindow* window, Map* map, Status* status);

  /** \brief Destructor
   */
  ~GraphicEngine();

  /** \brief Draws the whole scene
   **   calls others drawing functions
   */
  void drawScene();


private:
  /** \brief Sets up textures arrays, loading them only one time
   */
  void initSprites();

  /** \brief Draw map global background
   */
  void drawMap();

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
  void drawSelectionMenu(Cell* cell);

  /** \brief Draw Selection Menu
   ** selection menu pop when you select something
   ** fetches automatically cell on which the cursor is
   */
  void drawSelectionMenu();


  sf::RenderWindow* _window; ///< main rendering window
  Map* _map; ///< pointer on the global map
  Status* _status;

  // space left for rendering
  unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  unsigned int _renderY; ///< Drawable zone room left vertically (in px)

  int _gridOffsetX; ///< From where we start drawing horizontally (in px)
  int _gridOffsetY; ///< From where we start drawing vertically (in px)

  sf::Texture* _spritesUnits[E_UNITS_NB_UNITS]; ///< units sprites
  sf::Texture* _spritesTerrains[E_TERRAINS_NB_TERRAINS]; ///< terrains sprites
  sf::Texture* _spritesInterface[E_INTERFACE_NB_INTERFACE]; ///< interface sprites

  sf::Font _fontArmy; ///< menu font (US Army design)
};

#endif /* !GRAPHICENGINE_HH_ */
