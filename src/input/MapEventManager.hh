#ifndef MAPEVENTMANAGER_HH_
# define MAPEVENTMANAGER_HH_

#include <input/EventManager.hh>


/**
 * \class MapEventManager
 * \brief Process events related to the Map.
 */
class MapEventManager: public EventManager
{
public:
  bool process();

  void registerEvent(std::string key, std::function<void()> cb);
};


#endif /* !MAPEVENTMANAGER_HH_ */
