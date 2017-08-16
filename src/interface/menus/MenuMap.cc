#include <interface/menus/MenuMap.hh>
#include <common/Status.hh>


namespace interface {


void MenuMap::build()
{
  addCancelEntry( [=] { cancel(); } );

  auto entry(std::make_shared<MenuEntry> (e_entry::NEXT_TURN));
  entry->setCallback( [=] { game::Status::nextPlayer(); });
  _entries.push_back(entry);
}


} // namespace interface
