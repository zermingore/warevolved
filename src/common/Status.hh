#ifndef STATUS_HH_
# define STATUS_HH_

# include <common/include.hh>
# include <game/Map.hh>
# include <game/Cursor.hh>

// side panel possible positions
enum e_panel_position
{
  E_PANEL_DEACTIVATED = 0,
  E_PANEL_LEFT,
  E_PANEL_RIGHT
};

// menu bar possible positions
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
  explicit Status(Map* map);

  /** \brief Destructor
   */
  ~Status();

  /** \brief _cursor getter
   */
  Cursor* getCursor();
  e_panel_position getPanelPosition();
  e_menu_bar_position getMenuBarPosition();

  /** \brief Selection mode getter
   ** \return true if we're in selection mode; false otherwise
   */
  bool getSelectionActive();

  /** \brief notify the Status that a cell was clicked
   ** it sets up _selectionActive to
   **   true if we're now in selection mode
   **   false otherwise
   ** it also keeps clicked cell's coordinates in _selectedCell
   */
  void cellSelection();


private:
  Cursor* _cursor; ///< map Cursor
  Map* _map;

  // Interface Status
  e_panel_position _panelPosition; ///< Side panel position (if any)
  e_menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)

  bool _selectionActive; ///< true if we're in selection mode
  sf::Vector2f _selectedCell; ///< coordinates of the selected cell
};

#endif /* !STATUS_HH_ */
