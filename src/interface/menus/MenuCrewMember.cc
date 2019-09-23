/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewMember definition
 */


#include <interface/menus/MenuCrewMember.hh>
#include <game/Status.hh>


namespace interface {


void MenuCrewMember::build()
{
  addCancelEntry( [=] { cancel(); } );

  auto entry(std::make_shared<MenuEntry> (e_entry::NEXT_TURN));
  entry->setCallback( [=] { game::Status::nextPlayer(); });
  _entries.push_back(entry);
}


} // namespace interface
