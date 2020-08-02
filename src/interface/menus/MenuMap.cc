/**
 * \file
 * \date January 25, 2017
 * \author Zermingore
 * \namespace interface
 * \brief MenuMap class definition
 */

#include <game/Status.hh>
#include <interface/menus/MenuMap.hh>


namespace interface {


void MenuMap::build()
{
  addCancelEntry( [=, this] { cancel(); } );

  auto entry(std::make_shared<MenuEntry> (e_entry::NEXT_TURN));
  entry->setCallback( [=] { game::Status::nextPlayer(); });
  _entries.emplace_back(entry);
}


} // namespace interface
