/**
 * \file
 * \date May 20, 2013
 * \author Zermingore
 */

#ifndef MENU_ENTRY_HH_
# define MENU_ENTRY_HH_

# include <string>
# include <memory>
# include <functional>

# include <interface/InterfaceElement.hh>


namespace resources {
  class Text;
}


namespace interface {


/**
 * \enum e_entry
 * \brief entries descriptors
 */
enum class e_entry
{
  NONE = 0, // invalid selected entry

  MOVE,    // motion order
  WAIT,    // motion order
  PICK_UP, // motion order
  BOARD,   // motion order

  // crew
  DROP_OFF,
  GET_OUT,
  CREW,

  NEXT_TURN,
  ATTACK,

  CANCEL
};



/**
 * \class MenuEntry
 * \brief One entry (a clickable item) of a menu
 * \note The entry position is relative to the menu it belongs to.
 */
class MenuEntry: public InterfaceElement
{
public:
  /**
   * \brief deleted default constructor: we need to know the entry
   */
  MenuEntry() = delete;

  /**
   * \brief Constructor
   * \param entry Entry type to build.
   */
  explicit MenuEntry(const e_entry entry);

  /**
   * \brief returns entry Identifier, as a entries value
   */
  auto id() { return _id; }

  /**
   * \brief Executes the action matching the entry
   */
  void execute();

  /**
   * \brief _callback setter
   * \param callbacks List of Callbacks called when the menu entry is selected
   */
  void setCallbacks(const std::vector<std::function<void()>> callbacks) {
    _callbacks = callbacks;
  }

  /**
   * \brief _callback setter
   * \param callbacks List of Callbacks called when the menu entry is selected
   */
  void setCallback(const std::function<void()> callback) {
    _callbacks = { callback };
  }

  /**
   * \brief updates the graphical attributes of the entry
   */
  void update() override final;

  /**
   * \brief Draws label and sprite of the entry, calling the graphics engine
   */
  void draw() override final;



private:
  /**
   * \brief Initializes the label name
   * \param entry entry which associated name will be used
   */
  void setLabelName(e_entry entry);

  e_entry _id;                             ///< entry identifier
  std::shared_ptr<resources::Text> _label; ///< button label text
  std::string _labelName;                  ///< menu entry text

  /// callbacks list executed when the entry is selected
  std::vector<std::function<void()>> _callbacks;
};


} // namespace interface


#endif /* !MENU_ENTRY_HH_ */
