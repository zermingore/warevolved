/**
 * \file
 * \date July 25, 2013
 * \author Zermingore
 * \namespace interface
 * \brief InGameMenu class definition
 */

#include <interface/menus/InGameMenu.hh>

#include <game/Battle.hh>
#include <game/Player.hh>
#include <game/Status.hh>
#include <game/units/Unit.hh>
#include <graphics/Properties.hh>
#include <graphics/Sprite.hh>
#include <interface/Cursor.hh>
#include <interface/menus/MenuEntry.hh>



namespace interface {

InGameMenu::~InGameMenu()
{
  _lock.lock();
}


void InGameMenu::cancel()
{
  game::Status::popCurrentState();
}


void InGameMenu::addCancelEntry(const std::function<void()>& cancel_callback)
{
  auto entry_cancel{std::make_shared<MenuEntry> (e_entry::CANCEL)};
  entry_cancel->setCallback([=] { cancel_callback(); });

  _lock.lock();
  _entries.emplace_back(std::move(entry_cancel));
  _lock.unlock();
}



void InGameMenu::moveUp()
{
  decrementSelectedEntry();
}



void InGameMenu::moveDown()
{
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
  using p = graphics::Properties;

  _lock.lock();

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
  for (const auto& entry: _entries)
  {
    entry->setPosition({
      _position.x,
      _position.y + p::cellHeight() * static_cast<component> (entry_index)});
    entry->update();
    ++entry_index;
  }

  _lock.unlock();
}



e_entry InGameMenu::currentSelection()
{
  _lock.lock();
  auto idx{ _entries[_selectedEntry]->id() };
  _lock.unlock();

  return idx;
}



void InGameMenu::draw()
{
  update();

  _lock.lock();
  for (const auto& entry: _entries)
  {
    entry->draw();
  }
  _lock.unlock();

  _imageSelection->draw();
}


} // namespace interface
