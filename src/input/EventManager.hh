/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef INPUT_EVENT_MANAGER_HH_
# define INPUT_EVENT_MANAGER_HH_

# include <map>
# include <memory>
# include <functional>
# include <SFML/Window/Event.hpp>


class KeyManager;
enum class e_input;


/**
 * \class EventManager
 * \brief Process events.
 */
class EventManager
{
public:
  /**
   * \brief executes the callback matching the given event, if any
   * \return true if a callback was executed
   */
  bool process(const e_input input);


  /**
   * \brief Associates a callback to an event identified by key.
   * \param key event name.
   * \param cb callback to associate to the event.
   */
  void registerEvent(const e_input input, const std::function<void()> cb) {
    _callbacks[input] = cb;
  }


private:
  /**
   * \brief Looks for any released key.
   *   Reset the key timer matching the released key (if any)
   *   Reset switches if needed
   */
  void releasedKeys();

  /// callbacks / events association
  std::map<e_input, std::function<void()>> _callbacks;
};


#endif /* !INPUT_EVENT_MANAGER_HH_ */
