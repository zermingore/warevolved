#ifndef STATUS_HH_
# define STATUS_HH_

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

  /** \brief notify the Status that a cell was clicked
   ** it sets up _selectionActive to
   **   true if we're now in selection mode
   **   false otherwise
   ** it also keeps clicked cell's coordinates in _selectedCell
   */
  void cellSelection();

  // __________________________ Getters / Setters __________________________ //
  /** \brief returns selected cell's coordinates
   */
  inline Coords selectedCell() { return _selectedCell; }

  /** \brief returns current number of
   **   generated frames per Seconds
   ** \return number of fps
   ** \note if the compilation flag DEBUG_PERFS is not set
   **   the frame rate will be limited to 60
   **   it will be unlimited otherwise
   */
  inline float currentFPS() { return _currentFPS; }
  inline unsigned int cellWidth() { return _cellWidth; }
  inline unsigned int cellHeight() { return _cellHeight; }
  inline unsigned int gridThickness() { return _gridThickness; }
  inline unsigned int renderX() { return _renderX; }
  inline unsigned int renderY() { return _renderY; }
  inline unsigned int gridOffsetX() { return _gridOffsetX; }
  inline unsigned int gridOffsetY() { return _gridOffsetY; }
  unsigned int selectionMenuSelectedEntry();

  /** \brief current player identifier getter
   ** \return _currentPlayer: current player identifier
   */
  inline unsigned int currentPlayer() { return _currentPlayer; }

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
  // TODO Override with an optional parameter: pointer to get pop-ed mode
  State popCurrentMode();

  /** \brief \return current mode
   ** meaning, the summit of _modes stack
   */
  e_mode currentMode();

  /** \brief _window setter
   **   updates _renderX and _renderY
   */
  void setWindow(std::unique_ptr<sf::RenderWindow> window);

  // inline void windowClear() { _window->clear(); }

  // inline void windowDraw(const sf::Drawable &drawable) { _window->draw(drawable); }

  // inline bool windowPollEvent(sf::Event &event)
  // { return _window->pollEvent(event); }

  // inline void windowClose() { _window->close(); }
  // inline bool windowIsOpen() { return _window->isOpen(); }
  // inline void windowDisplay() { _window->display(); }

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  void pushMode(e_mode mode);

  /** \brief stacks a new mode on _modes
   ** \param mode mode we just entered
   */
  void pushModeInGameMenu(e_mode mode, InGameMenu *menu);

  /** \brief sets selected cell coordinates to the given coordinates
   ** \param c coordinates of the selected cell
   */
  inline void setSelectedCell(Coords c) { _selectedCell = c; }

  /** \brief sets current fps to the given value
   ** \param fps frame per second value
   */
  inline void setCurrentFPS(float fps) { _currentFPS = fps; }

  /** \brief sets cells width
   ** \param width cells width
   */
  inline void setCellWidth(unsigned int width) { _cellWidth = width; }

  /** \brief sets cells height
   ** \param height cells height
   */
  inline void setCellHeight(unsigned int height) { _cellHeight = height; }

  /** \brief sets grid thickness
   ** \param thickness graphical grid thickness
   */
  inline void setGridThickness(unsigned int t) { _gridThickness = t; }

  /** \brief sets drawable zone size width
   ** \param render_x new render zone width
   */
  inline void setRenderX(unsigned int x) { _renderX = x; }

  /** \brief sets drawable zone size height
   ** \param render_x new render zone height
   */
  inline void setRenderY(unsigned int y) { _renderY = y; }

  inline void setGridOffsetX(unsigned int x) { _gridOffsetX = x; }
  inline void setGridOffsetY(unsigned int y) { _gridOffsetY = y; }

  void setGridOffset();

  /** \brief sets _currentPlayer
   */
  inline void setCurrentPlayer(unsigned int id) { _currentPlayer = id; }

  inline std::shared_ptr<Battle> battle() { return _battle; }

  inline void setBattle(Battle b)
  { _battle = std::make_shared<Battle> (b); }


  inline unsigned int nbColumns() { return _nbColumns; }

  inline unsigned int nbLines() { return _nbLines; }

  inline void setNbColumns(unsigned int c) { _nbColumns = c; }

  inline void setNbLines(unsigned int l) { _nbLines = l; }

private:
  /** \brief resets render zone, sets it to window size
   */
  void resetRender();

  // TODO use a union with sfml, opengl, dx, ascii windows, ...
  // std::unique_ptr<sf::RenderWindow> _window; ///< main Rendering Window
  std::stack<std::shared_ptr<State>> _states; ///< States stack

  Coords _selectedCell; ///< coordinates of the selected cell
  float _currentFPS; ///< current number of generated frame per second
  unsigned int _nbColumns; ///< map number of columns
  unsigned int _nbLines; ///< map number of lines
  unsigned int _cellWidth; ///< cells width (in px)
  unsigned int _cellHeight; ///< cells height (in px)
  unsigned int _gridThickness; ///< cells delimiter thickness (in px)
  unsigned int _gridOffsetX; ///< x position from where we start drawing the grid
  unsigned int _gridOffsetY; ///< y position from where we start drawing the grid
  unsigned int _renderX; ///< Drawable zone room left horizontally (in px)
  unsigned int _renderY; ///< Drawable zone room left vertically (in px)
  std::shared_ptr<Battle> _battle; ///< pointer on Battle
  unsigned int _currentPlayer; ///< index in the _players array
};

#endif /* !STATUS_HH_ */
