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
  E_MENU_BAR_BOTTOM, // not sure we'll allow this

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

  /** \brief _cursor getter
   */
  inline std::shared_ptr<Cursor> cursor() { return _cursor; }

  /** \brief side panel position getter
   */
  inline e_panel_position panelPosition() { return _panelPosition; }

  /** \brief side panel position getter
   */
  inline e_menu_bar_position menuBarPosition() { return _menuBarPosition; }

  /** \brief sets panel position to the next position
   ** loops over the E_PANEL_NB_POSITIONS possibilities
   */
  void incrementPanelPosition();

  /** \brief sets menu bar position to the next position
   ** loops over the E_MENU_BAR_NB_POSITIONS possibilities
   */
  void incrementMenuBarPosition();

  /** \brief in-game menu getter
   ** \return _inGameMenu
   */
  inline std::shared_ptr<InGameMenu> inGameMenu() const { return _inGameMenu; }

  /** \brief PathFinding getter
   ** \return _path current path
   */
  inline std::shared_ptr<PathFinding> path() { return _path; }

  /** \brief sets the path origin
   ** meaning the cell from where it starts
   */
  inline void setPathOrigin(Coords coords) { _path->setOrigin(coords); }

  /** \brief draws all element relative to the user's interface
   ** meaning: in-game menus, panels and path (from path-finding)
   */
  void draw();


private:
  /** \brief Initializes Panel position
   */
  void setPanel();

  /** \brief Initializes Menu bar position
   */
  void setMenuBar();

  /** \brief Draw side panel
   */
  void drawPanel();

  /** \brief Draw menu bar
   */
  void drawMenuBar();

  std::shared_ptr<Cursor> _cursor; ///< Map Cursor
  std::shared_ptr<InGameMenu> _inGameMenu; ///< in game menu
  std::shared_ptr<PathFinding> _path; ///< current path
  e_panel_position _panelPosition; ///< Side panel position (if any)
  e_menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)
  bool _modificationPanel; ///< notification: panel status changed
  bool _modificationMenuBar; ///< notification: menu bar status changed
  unsigned int _panelX; ///< panel coordinates
  unsigned int _menuBarY; ///< menu bar coordinates
};

#endif /* !INTERFACE_HH_ */
