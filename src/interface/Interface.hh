#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/Cursor.hh>
# include <interface/menus/InGameMenu.hh>
# include <interface/panels/SidePanel.hh>
# include <interface/panels/MenuBar.hh>
# include <game/PathFinding.hh>


// TODO method draw: path, menus

/** \class Interface class
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

  ///< \brief _cursor getter
  inline std::shared_ptr<Cursor> cursor() { return _cursor; }

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

  ///< \brief changes _menubar position (DEACTIVATED, UP, DOWN)
  void nextMenuBarPosition();
  ///< \brief changes _panel position (DEACTIVATED, LEFT, RIGHT)
  void nextPanelPosition();

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
  std::shared_ptr<PathFinding> _path; ///< current path
  Panel_position _lastPanelPosition; ///< last known Side panel position
  MenuBar_position _lastMenuBarPosition; ///< last known Menu Bar position
  bool _modificationPanel; ///< notification: panel status changed
  bool _modificationMenuBar; ///< notification: menu bar status changed
};

#endif /* !INTERFACE_HH_ */
