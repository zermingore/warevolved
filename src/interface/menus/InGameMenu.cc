#include <interface/menus/InGameMenu.hh>

#include <game/Status.hh>
#include <game/Battle.hh>
#include <game/units/Unit.hh>
#include <game/Player.hh>
#include <interface/Cursor.hh>
#include <interface/menus/MenuEntry.hh>
#include <common/enums/states.hh>
#include <graphics/MapGraphicsProperties.hh>
#include <graphics/Sprite.hh>



namespace interface {


void InGameMenu::cancel() {
  game::Status::popCurrentState();
}


void InGameMenu::addCancelEntry(const std::function<void()> cancel_callback)
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


void InGameMenu::validate()
{
  // end validation (unit moved, ...) -> purge every menu
  _entries[_selectedEntry]->execute();
}



void InGameMenu::update()
{
  using namespace graphics;
  using p = MapGraphicsProperties;

  // _coords is filled by the player, with cursor coordinates
  _position = {
    static_cast<component> (_coords.c) * p::cellWidth()  + p::gridOffsetX(),
    static_cast<component> (_coords.l) * p::cellHeight() + p::gridOffsetY()};

  // highlighting current selection
  _imageSelection->setPosition(
    _position.x,
    _position.y + p::cellHeight() * static_cast<component> (_selectedEntry));

  // update entries positions
  auto entry_index(0);
  for (auto entry: _entries)
  {
    entry->setPosition({
      _position.x,
      _position.y + p::cellHeight() * static_cast<component> (entry_index)});
    entry->update();
    ++entry_index;
  }
}


/// \todo move in Dtor ?
void InGameMenu::close()
{
  // auto interface(game::Status::interface());
  // for (auto entry: _entries) {
  //   interface->removeElement(entry);
  // }

  // interface->removeElement(this); // apparently not needed, not sure why
}



e_entry InGameMenu::getCurrentSelection()
{
  return _entries[_selectedEntry]->id();
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
