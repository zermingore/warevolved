#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/enums/states.hh>


namespace interface {


void InGameMenu::build()
{
  switch (Status::state())
  {
    case e_state::ACTION_MENU:
    {
      PRINTF("-= Action menu =-");
      /// \todo check if there is a target
      auto entry(std::make_shared<MenuEntry> (e_entry::WAIT));
      entry->setCallback( [=] { waitUnit(); });
      _entries.push_back(entry);
      Status::interface()->addElement(entry);
      break;
    }

    case e_state::SELECTION_UNIT:
    case e_state::MENU:
      PRINTF("-= Selection menu =-");
      if (Status::battle()->map()->unit(_coords))
      {
        auto entry(std::make_shared<MenuEntry> (e_entry::MOVE));
        entry->setCallback( [=] { moveUnit(); });
        _entries.push_back(entry);
        Status::interface()->addElement(entry);
      }
      break;

    case e_state::PLAYING:
      break;

    default:
      Debug::error("InGameMenu::build Invalid State:", (int) Status::state());
      std::exit(1);
      assert(!"Invalid state found building menu");
      break;
  }

  // Whatever the menu is, we always add a 'Cancel' entry at the end
  auto entry(std::make_shared<MenuEntry> (e_entry::CANCEL));
  _entries.push_back(entry);
  Status::interface()->addElement(entry);
}


void InGameMenu::moveUp() {
  incrementSelectedEntry();
}

void InGameMenu::moveDown() {
  decrementSelectedEntry();
}


void InGameMenu::validate()
{
  // Cancel entry particular case (always the last one)
  if (_selectedEntry == _entries.size() - 1)
  {
    Status::interface()->popMenu();
//    close();
//    Status::popCurrentState();
    return;
  }

  _entries[_selectedEntry]->execute();
}


void InGameMenu::moveUnit()
{
  // Hiding but not deleting the current menu
  auto interface(Status::interface());
  for (auto entry: _entries) {
    interface->removeElement(entry);
  }

  Status::pushState(e_state::MOVING_UNIT);
}


void InGameMenu::waitUnit()
{
  // pop every State pushed since Playing (select, move unit)
  while (Status::state() != e_state::PLAYING) {
    Status::popCurrentState();
  }

  // Removing the interface elements of this menu
  for (auto entry: _entries) {
    Status::interface()->removeElement(entry);
  }

  // clearing the menu stack
  Status::interface()->clearMenu();
}


void InGameMenu::update(const std::shared_ptr<Map::MapGraphicsProperties> properties)
{
  auto width(properties->cellWidth());
  auto height(properties->cellHeight());

  // _coords is filled by the player, with cursor coordinates
  _position.x = _coords.x * width  + properties->gridOffsetX();
  _position.y = _coords.y * height + properties->gridOffsetY();

  // highlighting current selection
  Coords selected_entry_pos(_position.x, _position.y + height * _selectedEntry);
  _imageSelection.setPosition(selected_entry_pos);

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition(Coords(_position.x, _position.y + height * entry_index));
    ++entry_index;
  }
}



/// \todo move in Dtor ?
void InGameMenu::close()
{
  auto interface(Status::interface());
  for (auto entry: _entries) {
    interface->removeElement(entry);
  }
  // interface->removeElement(this); // apparently not needed, not sure why
}


void InGameMenu::draw() {
  _imageSelection.draw();
}


} // namespace interface
