#include <input/MapEventManager.hh>
#include <input/KeyManager.hh>

MapEventManager::MapEventManager()
{
  // sf::Keyboard::Left
  registerEvent(e_key::E_KEY_LEFT, [=] { moveCursorLeft(); });
}

void MapEventManager::moveCursorLeft()
{

}


bool MapEventManager::process()
{
  return true;
}


void MapEventManager::registerEvent(e_key key, std::function<void()> cb)
{

}
