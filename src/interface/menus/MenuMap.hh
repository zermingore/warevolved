/**
 * \file
 * \date January 25, 2017
 * \author Zermingore
 * \namespace interface
 * \brief MenuMap class declaration
 */

#ifndef MENU_MENU_MAP_HH_
# define MENU_MENU_MAP_HH_

# include <interface/menus/InGameMenu.hh>


namespace interface {


class MenuMap final: public InGameMenu
{
public:
  void build() override final;
};


} // namespace interface


#endif /* !MENU_MENU_MAP_HH_ */
