#ifndef STATUS_HH_
# define STATUS_HH_

# include <common/include.hh>
# include <common/mode.hh>
# include <game/Map.hh>
# include <interface/Cursor.hh>
# include <common/State.hh>
# include <stack>

/** \brief Side Panel possible positions
 */
enum e_panel_position
{
  E_PANEL_DEACTIVATED = 0,
  E_PANEL_LEFT,
  E_PANEL_RIGHT
};

/** \brief Menu Bar possible positions
 */
enum e_menu_bar_position
{
  E_MENU_BAR_DEACTIVATED = 0,
  E_MENU_BAR_TOP,
  E_MENU_BAR_BOTTOM
};


/** \brief stores game status information such as
 **   last cell selected, current player, ...
 */
class Status
{
public:
  /** \brief Default Constructor
   */
  Status();

  /** \brief Destructor
   */
  ~Status();

  /** \brief _cursor getter
   */
  Cursor* getCursor();
  e_panel_position getPanelPosition();
  e_menu_bar_position getMenuBarPosition();

  /** \brief returns selected cell's coordinates
   */
  Coords getSelectedCell();

  /** \brief notify the Status that a cell was clicked
   ** it sets up _selectionActive to
   **   true if we're now in selection mode
   **   false otherwise
   ** it also keeps clicked cell's coordinates in _selectedCell
   */
  void cellSelection();


  sf::RenderWindow *getWindow();
  Map *getMap();
  float getCurrentFPS();
  unsigned int getCellWidth();
  unsigned int getCellHeight();
  unsigned int getGridThickness();
  unsigned int getRenderX();
  unsigned int getRenderY();
  unsigned int getGridOffsetX();
  unsigned int getGridOffsetY();
  unsigned int getSelectionMenuSelectedEntry();


  /** \brief pops _modes summit
   ** exits the game if the stack is empty
   */
  void exitCurrentMode();

  /** \brief \return current mode
   ** meaning, the summit of _modes stack
   */
  e_mode getCurrentMode();


  /** \brief _window setter
   **   updates _renderX and _renderY
   */
  void setWindow(sf::RenderWindow *window);
  void setCursor(Cursor *cursor);
  void setMap(Map *map);
  void pushMode(e_mode mode); ///< stacks a new mode on _modes
  void setSelectedCell(Coords selected_cell);
  void setCurrentFPS(float current_fps);
  void setCellWidth(unsigned int cell_width);
  void setCellHeight(unsigned int cell_height);
  void setGridThickness(unsigned int grid_thickness);
  void setRenderX(unsigned int render_x);
  void setRenderY(unsigned int render_y);
  void setGridOffsetX(unsigned int grid_offset_x);
  void setGridOffsetY(unsigned int grid_offset_y);


private:
  // TODO use a union with sfml, opengl, dx, ascii windows, ...
  sf::RenderWindow *_window; ///< main Rendering Window
  Cursor *_cursor; ///< map Cursor
  Map *_map; ///< storing map

  // Interface Status
  e_panel_position _panelPosition; ///< Side panel position (if any)
  e_menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)
  std::stack<State*> _states; ///< States stack

  Coords _selectedCell; ///< coordinates of the selected cell
  float _currentFPS; ///< current number of generated frame per second

  // Cells Size
  unsigned int _cellWidth; ///< cells width (in px)
  unsigned int _cellHeight; ///< cells height (in px)

  // Graphic: space left for rendering
  unsigned int _gridThickness; ///< cells delimiter thickness (in px)

  unsigned int _gridOffsetX; ///< x position from where we start drawing the grid
  unsigned int _gridOffsetY; ///< y position from where we start drawing the grid

  unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  unsigned int _renderY; ///< Drawable zone room left vertically (in px)

  Coords _cursorSave; ///< Cursor position save
//  unsigned int _cursorSaveX; ///< Cursor position x coordinate save
//  unsigned int _cursorSaveY; ///< Cursor position y coordinate save
};

#endif /* !STATUS_HH_ */
