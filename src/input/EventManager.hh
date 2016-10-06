#ifndef EVENT_MANAGER_HH_
# define EVENT_MANAGER_HH_

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
  /// Constructor. Initializes the repetition timers.
  EventManager();

  /// Destructor
  virtual ~EventManager() {}


  /**
   * \brief check if a generic event (like closing the window) occurs
   *   calls matching functions if any
   * \return false if a quit request has been sent. True otherwise.
   */
  virtual bool process() { return true; }


  /**
   * \brief Associates a callback to an event identified by key.
   * \param key event name.
   * \param cb callback to associate to the event.
   */
  virtual void registerEvent(e_input key, std::function<void()> cb) {
//    _callbacks[key] = cb;
  }


  /**
   * \brief executes the callback matching the given event
   * \return true if a callback was executed
   */
//  bool execute(e_key key);


//  void processEvents();



private:
  /**
   * \brief Looks for any released key.
   *   Reset the key timer matching the released key (if any)
   *   Reset switches if needed
   */
  void releasedKeys();


//  sf::Event _event; ///< Event Manager

  /// callbacks / events association
  std::map<e_input, std::function<void()>> _callbacks;
};


#endif /* !EVENT_MANAGER_HH_ */
