/**
 * \file
 * \date May 21, 2013
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

#include <interface/Interface.hh>

#include <debug/Debug.hh>
#include <game/Status.hh>


namespace interface {


Interface::Interface(const graphics::Color c) {
  _settings = std::make_unique<InterfaceSettings> (c);
}


void Interface::addElement(const std::shared_ptr<InterfaceElement>& elt) {
  _elts.push_back(elt);
}


void Interface::removeElement(const std::shared_ptr<InterfaceElement>& elt)
{
  // Locating the right element to remove
  /// \todo (do not remove a graphical element based on its sprite name)
  for (const auto& it: _elts)
  {
    if (it->name() == elt->name()) {
      _elts.pop_back();
    }
  }
}


std::shared_ptr<InterfaceElement> Interface::element(const std::string& id)
{
  for (const auto& it: _elts)
  {
    if (it->name() == id) {
      return it;
    }
  }

# ifdef DEBUG
  ERROR("Interface: invalid element name request: ", id);
  PRINTF("displaying", _elts.size(), "element names");
  for (const auto& it: _elts)
  {
    PRINTF(" >", it->name());
  }
# endif // DEBUG

  return nullptr;
}


} // namespace interface
