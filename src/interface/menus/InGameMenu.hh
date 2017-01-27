/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 */

#ifndef IN_GAME_MENU_HH_
# define IN_GAME_MENU_HH_

# include <interface/menus/Menu.hh>

enum class e_state;

class Unit;

namespace interface {

/**
 * \class InGameMenu
 * \brief Refers to the menu called when
 *   A unit is picked
 *   A void cell is clicked
 */
class InGameMenu: public Menu
{
public:
  /**
   * \brief Builds the selection menu, filling the entries.
   */
  virtual void build() = 0;

  /**
   * \brief Closes the current menu, clearing its interface elements
   */
  virtual void close();


  /**
   * \brief Cursor motion: up
   */
  void moveUp();

  /**
   * \brief Cursor motion: down
   */
  void moveDown();

  /**
   * \brief Validate selected entry
   */
  void validate();


  /**
   * \brief updates the graphics attributes of the menu
   */
  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);

  /**
   * \brief Draw the entries of the menu
   */
  void draw();



protected:
  /**
   * \brief Default cancel entry callback (pops the menu)
   */
  virtual void cancel();

  /**
   * \brief Adds a cancel entry into the menu
   */
  void addCancelEntry(std::function<void()> cancel_callback);


  // \todo RM _cursorCoords / _unit
  // state data
  Coords _cursorCoords; ///< Saved cursor coordinates
  std::shared_ptr<Unit> _unit; ///< Saved unit
};


} // namespace interface


#endif /* !IN_GAME_MENU_HH_ */
