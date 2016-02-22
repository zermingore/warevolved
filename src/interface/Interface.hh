#ifndef INTERFACE_HH_
# define INTERFACE_HH_

/**
 * \file
 * \brief Interface class declaration.
 *
 * Manages all the User Interface.
 */


# include <interface/Cursor.hh>
# include <interface/InterfaceElement.hh>
// # include <interface/menus/InGameMenu.hh>
// # include <game/PathFinding.hh>


/**
 * \class Interface
 * \brief Keeps data relative to the user's interface.
 */
class Interface
{
public:
  /**
   * \brief Default Constructor
   *
   * Initializes in-game menu
   */
  Interface();


  /**
   * \brief _cursor getter
   *
   * \return Player's Cursor.
   */
  std::shared_ptr<Cursor> cursor() { return _cursor; }


  /**
   * \brief Interface elements vector getter.
   *
   * \return Elements of the interface.
   */
  std::vector<InterfaceElement>& elements() { return _elts; }


  /**
   * \brief Sets all element to draw.
   *
   * Sets coordinates of each elements.
   */
  void buildElements();


  /**
   * \brief in-game menu getter
   * \return _inGameMenu
   */
  //  std::shared_ptr<InGameMenu> inGameMenu() const { return _inGameMenu; }


  /**
   * \brief PathFinding getter
   * \return _path current path
   */
  //  std::shared_ptr<PathFinding> path() { return _path; }

  /**
   * \brief sets the path origin
   * meaning the cell from where it starts
   */
  //  void setPathOrigin(Coords coords) { _path->setOrigin(coords); }


private:
  std::shared_ptr<Cursor> _cursor; ///< Map Cursor
  std::vector<InterfaceElement> _elts; ///< list of elements

  //  std::shared_ptr<InGameMenu> _inGameMenu; ///< in game menu
  //  std::shared_ptr<PathFinding> _path; ///< current path
};

#endif /* !INTERFACE_HH_ */
