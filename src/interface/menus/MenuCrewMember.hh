/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewMember declaration
 */


#ifndef MENU_CREW_MEMBER_HH_
# define MENU_CREW_MEMBER_HH_

# include <interface/menus/InGameMenu.hh>


namespace interface {


class MenuCrewMember: public InGameMenu
{
public:
  void build() override final;
};


} // namespace interface


#endif /* !MENU_CREW_MEMBER_HH_ */
