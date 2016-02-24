#ifndef INTERFACE_HH_
# define INTERFACE_HH_

/**
 * \file
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

# include <vector>
# include <interface/InterfaceElement.hh>
# include <interface/InterfaceSettings.hh>
// # include <interface/menus/InGameMenu.hh>
// # include <game/PathFinding.hh>



namespace interface {

class Cursor;

/**
 * \class Interface
 * \brief Keeps data relative to the user's interface.
 */
class Interface
{
public:
  /// Deleted default constructor.
  Interface() = delete;

  /// Constructor. Initializes in-game menu.
  explicit Interface(Color c);

  /**
   * \brief Sets all element to draw.
   *
   * Sets coordinates of each elements.
   */
  void buildElements();


  /**
   * \brief cursor's getter.
   * \return Player's Cursor.
   */
  std::shared_ptr<Cursor> cursor() { return _cursor; }

  /**
   * \brief Interface elements vector getter.
   * \return Elements of the interface.
   */
  std::vector<InterfaceElement>& elements() { return _elts; }

  /**
   * \brief Cursor color getter.
   * \return Color of the cursor.
   */
  Color cursorColor() const { return _settings->cursorColor(); }

  /**
   * \brief Player's units color getter.
   * \return Units color.
   */
  Color unitsColor() const { return _settings->unitsColor(); }


  /**
   * \brief sets cursor color.
   * \param color _cursorColor value.
   */
  void setCursorColor(Color color) { _settings->setCursorColor(color); }

  /**
   * \brief sets units color.
   * \param color units color.
   */
  void setUnitsColor(Color color) { _settings->setUnitsColor(color); }


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
  std::unique_ptr<InterfaceSettings> _settings; ///< interface settings

  //  std::shared_ptr<InGameMenu> _inGameMenu; ///< in game menu
  //  std::shared_ptr<PathFinding> _path; ///< current path
};


} // namespace interface

#endif /* !INTERFACE_HH_ */
