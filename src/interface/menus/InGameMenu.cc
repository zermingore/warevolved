#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/units/Unit.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/enums/states.hh>
#include <graphics/MapGraphicsProperties.hh>


namespace interface {


void InGameMenu::cancel() {
  Status::popCurrentState();
}


void InGameMenu::addCancelEntry(std::function<void()> cancel_callback)
{
  auto entry_cancel(std::make_shared<MenuEntry> (e_entry::CANCEL));
  entry_cancel->setCallback( [=] { cancel_callback(); });
  _entries.push_back(entry_cancel);
}


void InGameMenu::moveUp() {
  decrementSelectedEntry();
}

void InGameMenu::moveDown() {
  incrementSelectedEntry();
}


void InGameMenu::validate() {
  // end validation (unit moved, ...) -> purge every menu
  _entries[_selectedEntry]->execute();
}



void InGameMenu::update()
{
  using p = graphics::MapGraphicsProperties;

  // _coords is filled by the player, with cursor coordinates
  _position.c = _coords.c * p::cellWidth()  + p::gridOffsetX();
  _position.l = _coords.l * p::cellHeight() + p::gridOffsetY();

  // highlighting current selection
  _imageSelection->setPosition(_position.c,
                               _position.l + p::cellHeight() * _selectedEntry);

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition(Coords(_position.c,
                              _position.l + p::cellHeight() * entry_index));
    entry->update();
    ++entry_index;
  }
}


/// \todo move in Dtor ?
void InGameMenu::close()
{
  // auto interface(Status::interface());
  // for (auto entry: _entries) {
  //   interface->removeElement(entry);
  // }

  // interface->removeElement(this); // apparently not needed, not sure why
}


void InGameMenu::draw()
{
  update();

  for (auto entry: _entries) {
    entry->draw();
  }

  _imageSelection->draw();
}


} // namespace interface
