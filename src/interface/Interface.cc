/**
 * \file
 * \author Zermingore
 * \brief Interface class definition.
 *
 * Manages the User Interface.
 */

#include <interface/Interface.hh>
#include <interface/menus/Menu.hh>


namespace interface {


Interface::Interface(Color c)
{
  _settings = std::make_unique<InterfaceSettings> (c);
}


void Interface::addElement(std::shared_ptr<InterfaceElement> elt)
{
  Debug::printf("interface addElement");
  _elts.push_back(elt);
}


void Interface::removeElement(std::shared_ptr<InterfaceElement> elt)
{
  // Locating the right element to remove
  /// \todo (do not remove a graphical element based on its sprite name)
  for (auto it: _elts)
  {
    if (it->name() == elt->name())
    {
      _elts.pop_back();
      Debug::printf("~");
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
  Debug::printf("displaying", _elts.size(), "element names");
  for (const auto it: _elts)
  {
    Debug::printf(" >", id);
  }
# endif // DEBUG

  return nullptr;
}

} // namespace interface
