/**
 * \file
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

#include <interface/Interface.hh>
#include <interface/menus/Menu.hh>
#include <common/Status.hh>


namespace interface {


Interface::Interface(Color c) {
  _settings = std::make_unique<InterfaceSettings> (c);
}


void Interface::addElement(std::shared_ptr<InterfaceElement> elt) {
  _elts.push_back(elt);
}


void Interface::removeElement(std::shared_ptr<InterfaceElement> elt)
{
  // Locating the right element to remove
  /// \todo (do not remove a graphical element based on its sprite name)
  for (auto it: _elts)
  {
    if (it->name() == elt->name()) {
      _elts.pop_back();
    }
  }
}


const std::shared_ptr<InterfaceElement> Interface::element(const std::string id)
{
  for (const auto it: _elts)
  {
    if (it->name() == id) {
      return it;
    }
  }

# ifdef DEBUG
  Debug::error("Interface: invalid element name request: ", id);
  PRINTF("displaying", _elts.size(), "element names");
  for (const auto it: _elts) {
    PRINTF(" >", id);
  }
# endif // DEBUG

  return nullptr;
}


void Interface::clearMenu()
{
  while (!_menus.empty()) {
    _menus.pop();
  }
}


void Interface::pushMenu(std::shared_ptr<Menu> menu)
{
  addElement(menu);
  _menus.push(menu);
}


void Interface::popMenu()
{
  assert(!_menus.empty() && "Interface menu stack empty");

  // Clearing current menu
  _menus.top()->close(); // always implemented ?
  _menus.pop();

  // Taking care of the previous menu (if any)
  if (!_menus.empty()) {
    _menus.top()->resume();
  }

  Status::popCurrentState();
}


} // namespace interface
