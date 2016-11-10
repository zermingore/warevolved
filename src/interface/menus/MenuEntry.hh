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
  STOP, // motion order
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
   * \brief updates the graphical attributes of the entry
   */
  void update(const std::shared_ptr<Map::MapGraphicsProperties> properties);


  void draw();


private:
  e_entry _id;                      ///< entry identifier
  std::string _background;          ///< background image name
  std::shared_ptr<sf::Text> _label; ///< button label text
  std::string _labelName;           ///< menu entry text
  Font _font;                       ///< button label font
};


} // namespace interface


#endif /* !MENU_ENTRY_HH_ */
