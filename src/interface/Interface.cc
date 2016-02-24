/**
 * \file
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

#include <interface/Interface.hh>
#include <interface/Cursor.hh>
#include <common/Status.hh>

namespace interface {


Interface::Interface(Color c)
{
  _settings = std::make_unique<InterfaceSettings> (c);
  _cursor = std::make_shared<Cursor> ();
  //  _path = std::make_shared<PathFinding> ();
  //  _inGameMenu = std::make_shared<InGameMenu> ();
}


void Interface::buildElements()
{
  InterfaceElement elt("cursor");
  elt.setPosition(_cursor->coords());
  elt.setRotation(45.);
  elt.setScale(.1);

  _elts.push_back(elt);

  //  auto mode = Status::currentMode();
  // if (mode == mode::MOVING_UNIT || mode == mode::ACTION_MENU)
  //   _path->drawPath();

  /// \todo get right inGameMenu
  //  if (mode == e_mode::SELECTION_MENU || mode == e_mode::ACTION_MENU)
  //    _inGameMenu->draw();
}


} // namespace interface
