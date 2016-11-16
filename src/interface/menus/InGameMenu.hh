/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 */

#ifndef IN_GAME_MENU_HH_
# define IN_GAME_MENU_HH_

# include <interface/menus/Menu.hh>

enum class e_state;


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
   * \brief default constructor.
   */
  InGameMenu() = default;

  /**
   * \brief Builds the selection menu, filling the entries.
   */
  void build();

  /**
   * \brief updates the graphics attributes of the menu
   */
  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);

  /**
   * \brief Highlights the selected entry
   */
  void draw();


  void close();
};


} // namespace interface


#endif /* !IN_GAME_MENU_HH_ */
