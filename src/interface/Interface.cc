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


Interface::Interface(const graphics::Color c)
  : _settings(std::make_unique<InterfaceSettings> (c))
{
}


void Interface::addElement(const std::shared_ptr<InterfaceElement>& elt) {
  _elts.emplace_back(elt);
}


void Interface::removeElement(const std::shared_ptr<InterfaceElement>& elt)
{
  /// \todo (do not remove a graphical element based on its sprite name)

  // Locating the elements to remove
  int index{0};
  std::vector<int> remove_indexes;
  for (const auto& it: _elts)
  {
    if (it->name() == elt->name()) {
      remove_indexes.push_back(index);
    }
    ++index;
  }

  for (const auto i: remove_indexes)
  {
    _elts.erase(_elts.begin() + i);
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
