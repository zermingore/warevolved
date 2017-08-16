/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 */

#ifndef EVENT_MANAGER_HH_
# define EVENT_MANAGER_HH_

# include <map>
# include <memory>
# include <functional>


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


#endif /* !EVENT_MANAGER_HH_ */
