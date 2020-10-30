/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 * \brief State class declaration and enum e_state definition
 */

#ifndef STATE_HH_
# define STATE_HH_

# include <mutex>
# include <memory>
# include <vector>
# include <common/using.hh>


class EventManager;

namespace interface {
  class InterfaceElement;
}

enum class e_state; // definition follows


/**
 * \class State
 * \brief Records a current state.
 *
 * Stores a state, which is composed of:
 *   a cursor position
 *   a state: \enum e_state index
 *   an event manager
 */
class State
{
public:
  /**
   * \brief Default constructor
   * \note Instantiates the EventManager
   */
  State();

  /**
   * \brief Default destructor
   */
  virtual ~State() = default;


  /**
   * \brief Set specific State's attributes
   * \param head head of the attributes list
   * \param attributes rest of the attributes list
   */
  template<typename Head, typename... Tail>
  void setAttributes(Head head, Tail... attributes)
  {
    setAttribute(head);
    setAttributes(attributes...);
  }

  /**
   * \brief Set the current attribute of the attributes list
   * \param head current head of the list
   */
  template<typename Attribute>
  void setAttribute(std::shared_ptr<Attribute> head) {
    _attributes.emplace_back(head);
  }

  /**
   * \brief Set attribute tail recursion (attributes list empty)
   */
  void setAttributes() { }


  /**
   * \brief Fetch the attributes from the _attributes vector
   */
  virtual void fetchAttributes() { }


  /**
   * \brief Function to call when the State is resumed
   *   (or executed for the first time)
   * \todo virtual pure
   */
  virtual void resume() { }


  /**
   * \brief Function to call when the State is suspended
   * \todo virtual pure
   */
  virtual void suspend() { }


  /**
   * \brief event manager getter
   * \return event manager
   */
  auto eventManager() {
    return _evtMgr;
  }


  /**
   * \brief returns the list of related interface elements
   */
  auto& interfaceElements() {
    return _interfaceElements;
  }


  /**
   * \brief Adds an InterfaceElement to manage
   * \param elt Element to add to the interface
   */
  void addInterfaceElement(std::shared_ptr<interface::InterfaceElement> elt) {
    _interfaceElements.emplace_back(elt);
  }


  /**
   * \brief Draw graphical elements related to the State.
   */
  virtual void draw();


  /// Cursor coordinates getter
  auto cursorCoords() {
    return _cursorCoords;
  }



protected:
  std::shared_ptr<EventManager> _evtMgr; ///< State related events

  /// Interface elements list
  std::vector<std::shared_ptr<interface::InterfaceElement>> _interfaceElements;

  Coords _cursorCoords; ///< Cursor's coordinates

  /// pointer on Abstract attribute
  std::vector<std::shared_ptr<void>> _attributes;


  std::mutex _lockDraw; ///< Lock draw while suspending
};



/**
 * \enum e_state
 * \brief various menu state values. Used to notify the state stack.
 */
enum class e_state: int
{
  NONE = 0,         ///< we should never be in this state

  GLOBAL,           ///< Default state, handling inputs accessible everywhere

  PLAYING,          ///< Browsing the map
  MAP_MENU,         ///< Generic map menu: next turn, ...
  EDIT_MAP,          ///< Browsing the map

  SELECTION_UNIT,   ///< Pick a Unit
  MOVING_UNIT,      ///< Move it
  ACTION_MENU,      ///< Give it an order (confirm move, switch to attack state)
  CREW_MANAGEMENT,  ///< Manage a Vehicle crew

  SELECTION_CREW,   ///< Select a member in a Unit crew

  SELECT_TARGET,    ///< Select a taget (attack, heal, ...)
  SELECT_DROP_ZONE, ///< Select a zone to drop a crew member

  BUILDING_MENU,    ///< Owned Building management
};


#endif /* !STATE_HH_ */
