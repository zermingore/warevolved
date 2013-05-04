#ifndef STATUS_HH_
# define STATUS_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <game/Cursor.hh>

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

/** \brief How we'll treat user's input
 ** it's sorted in sections, allowing compares like
 **   if (mode >= E_IN_GAME) do_something
 ** order more or less matches number of used keys
 */
enum e_event_mode
{
  E_EVENT_NONE = 0x00000000,

  E_EVENT_MAIN_MENU = 0x00000001,

  E_EVENT_IN_GAME = 0x00000010,
  E_EVENT_MAP_PLAYING = 0x00000011,
  E_EVENT_MENU_SELECTION = 0x00000012,
  E_EVENT_USER_INPUT
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
  // explicit Status(Map* map);

  /** \brief Destructor
   */
  ~Status();

  /** \brief _cursor getter
   */
  Cursor* getCursor();
  e_panel_position getPanelPosition();
  e_menu_bar_position getMenuBarPosition();

  /** \brief _selectionMode getter
   ** \return true if we're in selection mode, false otherwise
   */
  bool getSelectionMode();

  /** \brief Event mode getter
   ** \return Current event mode (in e_event_mode)
   */
  e_event_mode getEventMode();

  /** \brief returns selected cell's coordinates
   */
  sf::Vector2f getSelectedCell();

  /** \brief _selectionMode setter
   */
  void setSelectionMode(bool selection_mode);

  /** \brief notify the Status that a cell was clicked
   ** it sets up _selectionActive to
   **   true if we're now in selection mode
   **   false otherwise
   ** it also keeps clicked cell's coordinates in _selectedCell
   */
  void cellSelection();


  sf::RenderWindow * getWindow();
  Map *getMap();
  ResourcesManager *getRM();
  float getCurrentFPS();
  unsigned int getCellWidth();
  unsigned int getCellHeight();
  unsigned int getGridThickness();
  unsigned int getRenderX();
  unsigned int getRenderY();
  unsigned int getGridOffsetX();
  unsigned int getGridOffsetY();


  /** \brief _window setter
   **   updates _renderX and _renderY
   */
  void setWindow(sf::RenderWindow *window);
  void setCursor(Cursor *cursor);
  void setMap(Map *map);
  void setRM(ResourcesManager *rm);
  void setEventMode(e_event_mode event_mode);
  void setSelectedCell(sf::Vector2f selected_cell);
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
  ResourcesManager *_rm;

  // Interface Status
  e_panel_position _panelPosition; ///< Side panel position (if any)
  e_menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)
  e_event_mode _eventMode; ///< Remember the event mode we're in
  bool _selectionMode; ///< True if we're in selection mode
  sf::Vector2f _selectedCell; ///< coordinates of the selected cell
  float _currentFPS; ///< current number of generated frame per second

  // Cells Size
  unsigned int _cellWidth; ///< cells width (in px)
  unsigned int _cellHeight; ///< cells height (in px)

  // Graphic: space left for rendering
  unsigned int _gridThickness; ///< cells delimiter thickness (in px)

  unsigned int _gridOffsetX;
  unsigned int _gridOffsetY;

  unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  unsigned int _renderY; ///< Drawable zone room left vertically (in px)
};

#endif /* !STATUS_HH_ */
