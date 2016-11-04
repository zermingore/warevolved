/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 */

#ifndef INGAMEMENU_HH_
# define INGAMEMENU_HH_

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
  InGameMenu();

  /**
   * \brief Builds the selection menu, filling the entries.
   * \param state The state about to be pushed.
   */
  void build(/* e_state state */);

  /// \brief executes action matching the selected entry.
  void executeEntry();

  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);
};


} // namespace interface


#endif /* !INGAMEMENU_HH_ */
