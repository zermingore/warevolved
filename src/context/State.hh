/**
 * \file
 * \date July 24, 2013
 * \author Zermingore
 */

#ifndef STATE_HH_
# define STATE_HH_

# include <memory>
# include <vector>
# include <common/using.hh>


# include <debug/Debug.hh> // \todo remove !


class EventManager;

namespace interface {
  class InterfaceElement;
}

enum class e_state;


/**
 * \class State
 * \brief Records a current state.
 *
 * Stores a state, which is composed of:
 *   a cursor position
 *   a state: \enum state index
 *   an event manager
 */
class State
{
public:
  /**
   * \brief Default constructor. Instantiates the EventManager
   */
  State();

  /**
   * \brief Destructor.
   */
  ~State() = default;


  /**
   * \brief Set specific State's attributes
   * \param attributes Attributes list
   */
  // template<typename... Attributes>
  // virtual void setAttributes(Attributes... attributes) {}; /// \todo = 0

  void setAttributes() { PRINTF("[State] Done setting attributes"); }

  template<typename Head, typename... Tail>
  void setAttributes(Head head, Tail... attributes) {
    setAttribute(head);
    setAttributes(attributes...);
  }

  template<typename Attribute>
  void setAttribute(std::shared_ptr<Attribute> head) {
    _attributes.push_back(head);
    ERROR("[State] nb attr", _attributes.size());
  }



  /**
   * \brief Function to call when the State is resumed
   * (or executed for the first time)
   */
  virtual void resume() {} /// \todo =0

  /**
   * \brief Function to call when the State is suspended
   */
  virtual void suspend() {} /// \todo =0


  /**
   * \brief event manager getter
   * \return event manager
   */
  std::shared_ptr<EventManager> eventManager() { return _evtMgr; }

  /**
   * \brief returns the list of related interface elements
   */
  auto& interfaceElements() { return _interfaceElements; }

  /**
   * \brief Adds an InterfaceElement to manage
   * \param elt Element to add to the interface
   */
  void addInterfaceElement(std::shared_ptr<interface::InterfaceElement> elt) {
    _interfaceElements.push_back(elt);
  }

  /**
   * \brief Draw graphical elements related to the State.
   */
  virtual void draw();


protected:
  std::shared_ptr<EventManager> _evtMgr; ///< State related events

  ///< Interface elements list
  std::vector<std::shared_ptr<interface::InterfaceElement>> _interfaceElements;

  Coords _cursorCoords; ///< Cursor's coordinates

  std::vector<std::shared_ptr<void>> _attributes; ///< pointer on Abstract attribute

//  template <typename T> class _attr;

//  std::vector<template <typename T>> _attrs;
};


#endif /* !STATE_HH_ */
