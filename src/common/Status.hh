#ifndef STATUS_HH_
# define STATUS_HH_

# include <stack>
# include <common/enums/modes.hh>
# include <game/Map.hh>
# include <interface/menus/InGameMenu.hh>
# include <common/State.hh>
# include <game/Player.hh>


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

  /** \brief _window getter */
  sf::RenderWindow *getWindow();

  /** \brief _map getter */
  Map *getMap();

  /** \brief returns current number of
   **   generated frames per Seconds
   ** \return number of fps
   ** \note if the compilation flag DEBUG_PERFS is not set
   **   the frame rate will be limited to 60
   **   it will be unlimited otherwise
   */
  float getCurrentFPS();
  unsigned int getCellWidth();
  unsigned int getCellHeight();
  unsigned int getGridThickness();
  unsigned int getRenderX();
  unsigned int getRenderY();
  unsigned int getGridOffsetX();
  unsigned int getGridOffsetY();
  unsigned int getSelectionMenuSelectedEntry();

  std::vector<Player*> getPlayers();
  unsigned int getCurrentPlayer();


  /** \brief pops _modes summit
   ** exits the game if the stack is empty
   ** \param skip retrieve Cursor position or not
   */
  void exitCurrentMode(bool skip = false);

  /** \brief pops _modes summit while current mode <> mode
   ** exits the game if the stack is empty
   ** \param skip retrieve Cursor position or not
   */
  void exitToMode(e_mode mode, bool skip = false);

  /** \brief pops _modes and returns summit
   ** \return Menu of the top of the stack
   */
  State *popCurrentMode();

  /** \brief \return current mode
   ** meaning, the summit of _modes stack
   */
  e_mode getCurrentMode();

  /** \brief _window setter
   **   updates _renderX and _renderY
   */
  void setWindow(sf::RenderWindow *window);

  /** \brief sets map
   ** \param map current map
   */
  void setMap(Map *map);

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  void pushMode(e_mode mode);

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  void pushModeInGameMenu(e_mode mode, InGameMenu *menu);

  void setSelectedCell(Coords selected_cell);
  void setCurrentFPS(float current_fps);
  void setCellWidth(unsigned int cell_width);
  void setCellHeight(unsigned int cell_height);
  void setGridThickness(unsigned int grid_thickness);

  /** \brief sets drawable zone size width
   ** \param render_x new render zone width
   */
  void setRenderX(unsigned int render_x);

  /** \brief sets drawable zone size height
   ** \param render_x new render zone height
   */
  void setRenderY(unsigned int render_y);
  void setGridOffset();
  void setGridOffsetX(unsigned int grid_offset_x);
  void setGridOffsetY(unsigned int grid_offset_y);

  /** \brief sets _currentPlayer
   */
  void setCurrentPlayer(unsigned int current_player_id);

  /** \brief
   ** \param players
   */
  void setPlayers(std::vector<Player*> players);


private:
  /** \brief resets render zone, sets it to window size
   */
  void resetRender();


  // TODO use a union with sfml, opengl, dx, ascii windows, ...
  sf::RenderWindow *_window; ///< main Rendering Window
  Map *_map; ///< storing map
  std::stack<State*> _states; ///< States stack

  Coords _selectedCell; ///< coordinates of the selected cell
  float _currentFPS; ///< current number of generated frame per second

  unsigned int _cellWidth; ///< cells width (in px)
  unsigned int _cellHeight; ///< cells height (in px)
  unsigned int _gridThickness; ///< cells delimiter thickness (in px)
  unsigned int _gridOffsetX; ///< x position from where we start drawing the grid
  unsigned int _gridOffsetY; ///< y position from where we start drawing the grid
  unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  unsigned int _renderY; ///< Drawable zone room left vertically (in px)

  std::vector<Player*> _players; ///< array of players
  unsigned int _currentPlayer; ///< index in the _players array
};

#endif /* !STATUS_HH_ */
