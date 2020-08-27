/**
 * \file
 * \date April 17, 2013
 * \author Zermingore
 * \brief EventManager class declaration and enum e_input definition
 */

#ifndef EVENT_MANAGER_HH_
# define EVENT_MANAGER_HH_

# include <map>
# include <memory>
# include <functional>


class KeyManager;
enum class e_input; // definition follows


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
   * \param input event to link with the callback.
   * \param cb callback to associate to the event.
   */
  void registerEvent(const e_input input, const std::function<void()> cb) {
    _callbacks[input] = cb;
  }


private:
  /**
   * \brief Looks for any released key.
   * \note Reset the key timer matching the released key (if any)
   * \note Reset switches if needed
   */
  void releasedKeys();

  /// Callbacks / events association
  std::map<e_input, std::function<void()>> _callbacks;
};



/**
 * \enum e_input
 * \brief Logical input names
 * \warning New inputs should be added at the end of the list
 *   (as tests replay rely on the values)
 */
enum class e_input
{
  // Motion keys
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,

  // Action keys
  SELECTION,

  // Interface keys
  TOGGLE_PANEL,

  // Global inputs
  SCREENSHOT,
  DUMP_MAP,
  QUICK_SAVE,
  QUICK_LOAD,

  // Exit requests
  EXIT,

  // Editor
  EDIT_TERRAIN_NEXT,
  EDIT_UNIT_NEXT,
  EDIT_UNIT_DEL,

  NB_KEYS
};


#endif /* !EVENT_MANAGER_HH_ */
