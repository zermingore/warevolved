#ifndef MENU_ENTRY_HH_
# define MENU_ENTRY_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>
# include <interface/InterfaceElement.hh>


namespace interface {


/**
 * \brief entries descriptors
 */
enum class e_entry
{
  NONE = 0, // invalid selected entry

  MOVE, // motion order
  WAIT, // motion order
  NEXT_TURN,
  ATTACK,

  CANCEL
};



/**
 * \class MenuEntry
 * \brief One entry (a clickable item) of a menu
 *
 * Its position is relative to the menu it belongs to.
 */
class MenuEntry: public InterfaceElement
{
public:
  /**
   * \brief deleted default constructor
   */
  MenuEntry() = delete;

  /**
   * \brief Constructor
   * \param entry Entry type to build.
   */
  explicit MenuEntry(e_entry entry);

  /**
   * \brief returns entry Identifier, as a entries value
   */
  e_entry id() { return _id; }

  /**
   * \brief Executes the action matching the entry
   */
  void execute();

  /**
   * \brief _callback setter
   * \param callback Callback called when the menu entry is selected
   */
  void setCallback(std::function<void()> callback) { _callback = callback; }

  /**
   * \brief updates the graphical attributes of the entry
   */
  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);

  /**
   * \brief Draws label and sprite of the entry, calling the graphics engine
   */
  void draw();



private:
  /**
   * \brief Initializes the label name
   * \param entry entry which associated name will be used
   */
  void setLabelName(e_entry entry);

  e_entry _id;                      ///< entry identifier
  std::shared_ptr<sf::Text> _label; ///< button label text
  std::string _labelName;           ///< menu entry text
  resources::Font _font;            ///< button label font

  /// callback executed when the entry is selected
  std::function<void()> _callback;
};


} // namespace interface


#endif /* !MENU_ENTRY_HH_ */
