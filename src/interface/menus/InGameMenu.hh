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
  void build() final;


  void moveUp();
  void moveDown();

  /**
   * \brief updates the graphics attributes of the menu
   */
  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);

  /**
   * \brief Highlights the selected entry
   */
  void draw();


  /**
   * \brief Closes the current menu, clearing its interface elements
   */
  void close();


  void validate();


  /// \todo should not be there
  void moveUnit();

  void waitUnit();



private:
  /**
   * \brief Default cancel entry callback (pops the menu)
   */
  void defaultCancel();

  /**
   * \brief Action cancel entry callback
   */
  void actionCancel();

  /**
   * \brief Restore menu to its previous state
   */
  void restore();

  /**
   * \brief Adds a standard cancel entry into the menu
   */
  void addCancelEntry(std::function<void()> cancel_callback);


  // state data
  Coords _cursorCoords; ///< Saved cursor coordinates
  std::shared_ptr<Unit> _unit; ///< Saved unit
};


} // namespace interface


#endif /* !IN_GAME_MENU_HH_ */
