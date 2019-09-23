/**
 * \file
 * \date September 23, 2019
 * \author Zermingore
 * \brief interface::MenuCrewBrowse definition
 */


#include <interface/menus/MenuCrewBrowse.hh>

#include <interface/menus/MenuEntry.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <context/State.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <game/units/Unit.hh>
#include <game/PathFinding.hh>

#include <debug/Debug.hh>


namespace interface {



MenuCrewBrowse::MenuCrewBrowse()
{
}



void MenuCrewBrowse::build()
{
  auto entry_wait(std::make_shared<MenuEntry> (e_entry::WAIT)); /// \todo MenuEntryCrew
  entry_wait->setCallback( [=] { });
  _entries.push_back(entry_wait);

  addCancelEntry( [=] { cancel(); } );
}



void MenuCrewBrowse::cancel()
{
  game::Status::clearStates();
}



void MenuCrewBrowse::draw()
{
  InGameMenu::draw(); /// \todo draw units
}


} // namespace interface
