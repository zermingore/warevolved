#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/Cursor.hh>
# include <interface/menus/InGameMenu.hh>
# include <game/PathFinding.hh>


/** \brief Side Panel possible positions
 */
enum e_panel_position
{
  E_PANEL_DEACTIVATED = 0,
  E_PANEL_LEFT,
  E_PANEL_RIGHT,

  E_PANEL_NB_POSITIONS // useful with modulo (++position % nb)
};

/** \brief Menu Bar possible positions
 */
enum e_menu_bar_position
{
  E_MENU_BAR_DEACTIVATED = 0,
  E_MENU_BAR_TOP,
  E_MENU_BAR_BOTTOM,

  E_MENU_BAR_NB_POSITIONS // useful with modulo (++position % nb)
};


// TODO method draw: path, menus

/** \brief Interface class
 ** keeps data relative to the user's interface
 ** draws the user's interface
 */
class Interface
{
public:
  /** Default Constructor
   ** Initializes in-game menu
   */
  Interface();

  /** Destructor
   */
  ~Interface();

  /** \brief _cursor getter
   */
  Cursor *getCursor();

  /** \brief side panel position getter
   */
  e_panel_position getPanelPosition();

  /** \brief side panel position getter
   */
  e_menu_bar_position getMenuBarPosition();

  /** \brief sets panel position to the next position
   ** loops over the E_PANEL_NB_POSITIONS possibilities
   */
  void incrementPanelPosition();

  /** in-game menu getter
   ** \return _inGameMenu
   */
  InGameMenu *getInGameMenu();

  /** \brief PathFinding getter
   */
  PathFinding *getPath();

  /** \brief sets the path origin
   ** meaning the cell from where it starts
   */
  void setPathOrigin(Coords coords);

  /** \brief draws all element relative to the user's interface
   ** meaning: in-game menus, panels and path (from path-finding)
   */
  void draw();


private:
  Cursor *_cursor; ///< Map Cursor
  InGameMenu *_inGameMenu; ///< in game menu
  PathFinding *_path; ///< current path
  e_panel_position _panelPosition; ///< Side panel position (if any)
  e_menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)
};

#endif /* !INTERFACE_HH_ */
