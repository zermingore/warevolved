#ifndef INTERFACE_HH_
# define INTERFACE_HH_

# include <interface/Cursor.hh>
# include <interface/menus/InGameMenu.hh>
# include <game/PathFinding.hh>


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
};

#endif /* !INTERFACE_HH_ */
