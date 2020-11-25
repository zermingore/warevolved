/**
 * \file
 * \date May 20, 2013
 * \author Zermingore
 * \namespace interface
 * \brief MenuEntry class declaration and e_entry enum definition
 */

#ifndef MENU_ENTRY_HH_
# define MENU_ENTRY_HH_

# include <string>
# include <memory>
# include <mutex>
# include <functional>

# include <interface/InterfaceElement.hh>


namespace resources {
  class Text;
}

enum class e_entry; // definition follows


namespace interface {


/**
 * \class MenuEntry
 * \brief One entry (a clickable item) of a menu
 * \note The entry position is relative to the menu it belongs to.
 * \note Motherclass of MenuEntryCrew
 */
class MenuEntry: public InterfaceElement
{
public:
  /**
   * \brief deleted default constructor: we need to know at least the entry
   */
  MenuEntry() = delete;

  /**
   * \brief Constructor
   * \param entry Entry type to build
   * \param wide Display the entry as wide?
   */
  explicit MenuEntry(const e_entry entry, bool wide = false);

  /**
   * \brief Constructor
   * \param label Entry text
   * \param sprite to draw on the entry
   * \param notes Additional text to display
   */
  MenuEntry(const std::string label,
            const graphics::Sprite &sprite,
            std::string notes);

  /**
   * \brief Destructor
   */
  virtual ~MenuEntry() override = default;

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
  void setCallbacks(const std::vector<std::function<void()>>& callbacks) {
    _callbacks = callbacks;
  }

  /**
   * \brief _callback setter
   * \param callback Callback called when the menu entry is selected
   */
  void setCallback(const std::function<void()> callback) {
    _callbacks = { callback };
  }

  /**
   * \brief updates the graphical attributes of the entry
   */
  void update() override;

  /**
   * \brief Draws label and sprite of the entry, calling the graphics engine
   */
  virtual void draw() override;



protected:
  /**
   * \brief Initializes the label name
   * \param entry entry which associated name will be used
   */
  void setLabelName(e_entry entry);

  e_entry _id;                             ///< entry identifier
  std::shared_ptr<resources::Text> _label; ///< button label text
  std::string _labelName;                  ///< menu entry text

  bool _wide; ///< Wide entry?
  std::shared_ptr<graphics::Sprite> _extraSprite; ///< ex: Unit sprite
  std::string _notes; ///< Extra text notes

  /// callbacks list executed when the entry is selected
  std::vector<std::function<void()>> _callbacks;

  std::mutex _lock; ///< Prevent updating old entries
};


} // namespace interface



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
  CREW_CONFIRM, // Confirm the crew actions (not reversible)

  NEXT_TURN,
  ATTACK,

  // Buildings
  ENTER_BUILDING,
  INVESTIGATE,
  CONTROL,
  LEAVE,
  COLLECT,
  LOAD,
  EXIT_BUILDING,
  UNITS_BUILDING,

  CANCEL
};


#endif /* !MENU_ENTRY_HH_ */
