/**
 * \file
 * \date September 22, 2019
 * \author Zermingore
 * \brief StateMenuCrew definition
 */


#include <context/StateMenuCrew.hh>

#include <debug/Debug.hh>

#include <input/EventManager.hh>
#include <common/enums/input.hh>
#include <common/enums/states.hh>
#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/units/Unit.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuCrewBrowse.hh>
#include <interface/menus/MenuCrewMember.hh>



StateMenuCrew::StateMenuCrew()
  : State()
  , _menuCrewCoords(10,10)
  , _browseMembers(true)
{
  // browsing entries
  _evtMgr->registerEvent(e_input::MOVE_UP,    [=] { moveUp();    });
  _evtMgr->registerEvent(e_input::MOVE_DOWN,  [=] { moveDown();  });
  _evtMgr->registerEvent(e_input::MOVE_LEFT,  [=] { moveLeft();  });
  _evtMgr->registerEvent(e_input::MOVE_RIGHT, [=] { moveRight(); });

  _evtMgr->registerEvent(e_input::SELECTION,  [=] { validate(); });
  _evtMgr->registerEvent(e_input::EXIT,       [=] { exit();     });

  _menuCrew   = std::make_unique<interface::MenuCrewBrowse> ();
  _menuMember = std::make_unique<interface::MenuCrewMember> ();
}



void StateMenuCrew::suspend()
{
  /// \todo set menu at optimal coordinates (avoid hiding units for instance)
  _menuCrewCoords = _menuCrew->coords();
}


void StateMenuCrew::resume()
{
  // retrieve coordinates from the attributes
  if (_attributes.size())
  {
    fetchAttributes();
  }

  _menuCrew->setCoords(_menuCrewCoords);
  _menuCrew->build();

  _menuMemberCoords = _menuCrewCoords;
  _menuMemberCoords.x += 4; /// \todo hard-coded
  _menuMember->setCoords(_menuMemberCoords);
  _menuMember->build();
}



void StateMenuCrew::moveUp()
{
  using namespace interface;

  if (_browseMembers)
  {
    _menuCrew->decrementSelectedEntry();

    // Hide or reveal the menu depending on the entry we currently hightlight
    if (   _menuCrew->getCurrentSelection() == e_entry::CANCEL
        || _menuCrew->getCurrentSelection() == e_entry::CREW_CONFIRM)
    {
      _menuMember->setHidden(true);
    }
    else
    {
      _menuMember->setHidden(false);
    }
  }
  else
  {
    _menuMember->decrementSelectedEntry();
  }
}



void StateMenuCrew::moveDown()
{
  using namespace interface;

  if (_browseMembers)
  {
    _menuCrew->incrementSelectedEntry();

    // Hide or reveal the menu depending on the entry we currently hightlight
    if (   _menuCrew->getCurrentSelection() == e_entry::CANCEL
        || _menuCrew->getCurrentSelection() == e_entry::CREW_CONFIRM)
    {
      _menuMember->setHidden(true);
    }
    else
    {
      _menuMember->setHidden(false);
    }
  }
  else
  {
    _menuMember->incrementSelectedEntry();
  }
}



void StateMenuCrew::moveRight()
{
  // No member menu next to 'Confirm' and 'Cancel'
  if (   _menuCrew->getCurrentSelection() == interface::e_entry::CANCEL
      || _menuCrew->getCurrentSelection() == interface::e_entry::CREW_CONFIRM)
  {
    return;
  }

  _browseMembers = false;
  _menuMember->setActive(true);
  _menuCrew->setActive(false);
}



void StateMenuCrew::moveLeft()
{
  _browseMembers = true;
  _menuCrew->setActive(true);
  _menuMember->setActive(false);
  _menuMember->resetSelectedEntry();
}



void StateMenuCrew::validate()
{
  if (_browseMembers)
  {
    if (_menuCrew->getCurrentSelection() == interface::e_entry::CANCEL)
    {
      game::Status::clearStates();
      return;
    }

    if (_menuCrew->getCurrentSelection() == interface::e_entry::CREW_CONFIRM)
    {
      game::Status::battle()->map()->selectedUnit()->setPlayed(true);
      game::Status::clearStates();
      return;
    }

    moveRight(); // same behaviour
    return;
  }

  if (_menuMember->getCurrentSelection() == interface::e_entry::CANCEL)
  {
    exit();
  }

  _menuMember->validate();
}



void StateMenuCrew::exit() // escape key
{
  if (!_browseMembers)
  {
    _browseMembers = true;
    _menuCrew->setActive(true);
    _menuMember->setActive(false);
    _menuMember->resetSelectedEntry();
    return;
  }

  game::Status::clearStates();
}



void StateMenuCrew::fetchAttributes()
{
  if (!_attributes.size())
  {
    ERROR("StateMenu::fetchAttributes called without available attributes");
    assert(!"No attribute found");
    return;
  }

  auto p = std::static_pointer_cast<Coords> (_attributes[0]);
  _menuCrewCoords.c = p->c;
  _menuCrewCoords.l = p->l;

  _menuMemberCoords = _menuCrewCoords;
  _menuMemberCoords.x += 4; /// \todo hard-coded

  /// \todo fetch selected and hovered units?

  // reset the attributes vector
  _attributes.clear();
}



void StateMenuCrew::draw()
{
  _menuCrew->draw();
  _menuMember->draw();
}
