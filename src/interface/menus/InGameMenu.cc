#include <common/Status.hh>
#include <game/applications/Battle.hh>
#include <game/units/Unit.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <interface/menus/InGameMenu.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/enums/states.hh>



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
  incrementSelectedEntry();
}

void InGameMenu::moveDown() {
  decrementSelectedEntry();
}


void InGameMenu::validate() {
  // end validation (unit moved, ...) -> purge every menu
  _entries[_selectedEntry]->execute();
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
  _imageSelection->setPosition(selected_entry_pos);

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition(Coords(_position.x, _position.y + height * entry_index));
    entry->update(properties);
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
  update(Status::battle()->map()->graphicsProperties());

  for (auto entry: _entries) {
    entry->draw();
  }

  _imageSelection->draw();
}


} // namespace interface
