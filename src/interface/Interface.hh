#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/Cursor.hh>
# include <interface/menus/InGameMenu.hh>
# include <interface/panels/SidePanel.hh>
# include <interface/panels/MenuBar.hh>
// # include <game/PathFinding.hh>


/** \brief Side Panel possible positions
 */
enum class panel_position
{
  DEACTIVATED = 0,
  LEFT,
  RIGHT,

  NB_POSITIONS // useful with modulo (++position % nb)
};

/** \brief Menu Bar possible positions
 */
enum class menu_bar_position
{
  DEACTIVATED = 0,
  TOP,
  BOTTOM, // not sure we'll allow this

  NB_POSITIONS // useful with modulo (++position % nb)
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
  std::shared_ptr<Cursor> cursor() { return _cursor; }

  /** \brief side panel position getter
   */
  panel_position panelPosition() { return _panelPosition; }

  /** \brief side panel position getter
   */
  menu_bar_position menuBarPosition() { return _menuBarPosition; }

  /** \brief sets panel position to the next position
   ** loops over the panel::NB_POSITIONS possibilities
   */
  void incrementPanelPosition();

  /** \brief sets menu bar position to the next position
   ** loops over the menu_bar::NB_POSITIONS possibilities
   */
  void incrementMenuBarPosition();

  /** \brief in-game menu getter
   ** \return _inGameMenu
   */
  std::shared_ptr<InGameMenu> inGameMenu() const { return _inGameMenu; }

  /** \brief PathFinding getter
   ** \return _path current path
   */
//  std::shared_ptr<PathFinding> path() { return _path; }

  /** \brief sets the path origin
   ** meaning the cell from where it starts
   */
//  void setPathOrigin(Coords coords) { _path->setOrigin(coords); }

  /** \brief draws all element relative to the user's interface
   ** meaning: in-game menus, panels and path (from path-finding)
   */
  void draw();


private:
  /** \brief Initializes Panel position
   */
  void setSidePanel();

  /** \brief Initializes Menu bar position
   */
  void setMenuBar();

  /** \brief Draw side panel
   */
  void drawSidePanel();

  /** \brief Draw menu bar
   */
  void drawMenuBar();

  std::shared_ptr<Cursor> _cursor; ///< Map Cursor
  std::shared_ptr<InGameMenu> _inGameMenu; ///< in game menu
  std::shared_ptr<SidePanel> _panel; ///< side menu
  std::shared_ptr<MenuBar> _menuBar; ///< menuBar
  panel_position _panelPosition; ///< Side panel position (if any)
  menu_bar_position _menuBarPosition; ///< Menu Bar position (if any)
  bool _modificationPanel; ///< notification: panel status changed
  bool _modificationMenuBar; ///< notification: menu bar status changed

  //  std::shared_ptr<PathFinding> _path; ///< current path
};

#endif /* !INTERFACE_HH_ */
