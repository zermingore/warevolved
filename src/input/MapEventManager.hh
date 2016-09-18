#ifndef MAPEVENTMANAGER_HH_
# define MAPEVENTMANAGER_HH_

#include <input/EventManager.hh>
#include <input/KeyManager.hh>


/**
 * \class MapEventManager
 * \brief Process events related to the Map.
 */
class MapEventManager: public EventManager /// \todo inherit from another class
{
public:
  MapEventManager();

  /**
   * \brief try to process the given event.
   * \param event event to process.
   * \return true if the event was processed, false otherwise.
   */
  bool process(/* event*/);

  void registerEvent(e_key key, std::function<void()> cb);

  void moveCursorLeft();
};


#endif /* !MAPEVENTMANAGER_HH_ */
