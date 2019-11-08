#include <game/Status.hh>
#include <interface/menus/MenuMap.hh>


namespace interface {


void MenuMap::build()
{
  addCancelEntry( [=, this] { cancel(); } );

  auto entry(std::make_shared<MenuEntry> (e_entry::NEXT_TURN));
  entry->setCallback( [=, this] { game::Status::nextPlayer(); });
  _entries.push_back(entry);
}


} // namespace interface
