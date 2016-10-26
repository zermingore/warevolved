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
}

void Interface::updateElements()
{
  // unused grepme
  // call update on all elements
}


void Interface::addElement(std::shared_ptr<InterfaceElement> elt)
{
  _elts.push_back(elt);
}


} // namespace interface
