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
#include <game/Player.hh>
#include <game/PathFinding.hh>
#include <interface/menus/Menu.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuMap.hh>
#include <interface/menus/MenuCrewBrowse.hh>
#include <interface/menus/MenuCrewMember.hh>
#include <interface/Cursor.hh>



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

  _menuCrew = std::make_unique<interface::MenuCrewBrowse> ();
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
  if (_browseMembers)
  {
    _menuCrew->decrementSelectedEntry();
  }
  else
  {
    _menuMember->decrementSelectedEntry();
  }
}



void StateMenuCrew::moveDown()
{
  if (_browseMembers)
  {
    _menuCrew->incrementSelectedEntry();
  }
  else
  {
    _menuMember->incrementSelectedEntry();
  }
}



void StateMenuCrew::moveRight()
{
  _browseMembers = false;
}



void StateMenuCrew::moveLeft()
{
  _browseMembers = true;
}



void StateMenuCrew::validate()
{
  if (_browseMembers)
  {
    _browseMembers = false;
    return;
  }
  _menuMember->validate();
}



void StateMenuCrew::exit()
{
  if (!_browseMembers)
  {
    _browseMembers = true;
    return;
  }

  game::Status::popCurrentState();
  game::Status::currentState()->resume();
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
