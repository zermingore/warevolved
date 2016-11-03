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



const std::shared_ptr<InterfaceElement> Interface::element(const std::string id)
{
  for (const auto it: _elts)
  {
    if (it->name() == id)
      return it;
  }

# ifdef DEBUG
  Debug::error("Interface: invalid element name request: ", id);
  Debug::printf("displaying", _elts.size(), "element names");
  for (const auto it: _elts)
  {
    Debug::printf(" >", id);
  }
# endif // DEBUG

  return nullptr;
}

} // namespace interface
