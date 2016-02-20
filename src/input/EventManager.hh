#ifndef EVENT_HH_
# define EVENT_HH_

# include <map>
# include <memory>
# include <functional>
# include <SFML/Window.hpp>


class KeyManager;

/** \class processing event class
 */
class EventManager
{
public:
  /**
   * \brief Constructor
   *   processes input events
   */
  EventManager();

  /**
   * \brief check if a generic event (like closing the window) occurs
   *   calls matching functions if any
   * \return false if a quit request has been sent
   *   true otherwise
   */
  bool process();


  /**
   * \brief associates a callback to an event identified by key
   * \param key event name
   * \param cb callback to associate to the event
   */
  void registerEvent(std::string key, std::function<void()> cb) {
    _callbacks[key] = cb;
  }

  /**
   * \brief executes the callback matching the given event
   * \return true if a callback was executed
   */
  bool execute(std::string key);



private:
  /**
   * \brief Processes events relative to
   * - right panel requests (show, save game, ...)
   * - menu bar
   */
  void panels();

  /**
   * \brief Processes events while we're in the selection menu
   *   (for example arrows do not move game cursor but menu cursor)
   * \param menu menu of which we want to manage events
   */
  void selectionMenu();

  /**
   * \brief select a cell
   *   browse Cells containing an available target on keyboard strikes
   */
  void selectTarget();

  /**
   * \brief Processes events while moving a unit
   */
  void moveUnit();

  /**
   * \brief Processes all game events
   * called when we're not browsing a menu, moving a unit, ...
   * \return false if we got an exit request true otherwise
   */
  bool game();

  /**
   * \brief Looks for any released key.
   *   Reset the key timer matching the released key (if any)
   *   Reset switches if needed
   */
  void releasedKeys();


  sf::Event _event; ///< Event Manager
  std::shared_ptr<KeyManager> _km; ///< KeyManager instance

  ///< callbacks / events association
  std::map<std::string, std::function<void()>> _callbacks;
};

#endif /* !EVENT_HH_ */
