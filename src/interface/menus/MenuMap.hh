/**
 * \file
 * \date January 25, 2017
 * \author Zermingore
 * \brief interface::MenuMap declaration
 */


#ifndef MENU_MENU_MAP_HH_
# define MENU_MENU_MAP_HH_

# include <interface/menus/InGameMenu.hh>


namespace interface {


class MenuMap: public InGameMenu
{
public:
  void build();
};


} // namespace interface


#endif /* !MENU_MENU_MAP_HH_ */
