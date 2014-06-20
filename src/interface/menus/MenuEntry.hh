#ifndef MENUENTRY_HH_
# define MENUENTRY_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>


// TODO add execute method given to ctor

/** \brief entries descriptors
 */
enum e_entry
{
  E_ENTRY_NONE = 0, // invalid selected entry

  E_ENTRY_MOVE, // motion order
  E_ENTRY_STOP, // motion order
  E_ENTRY_NEXT_TURN,
  E_ENTRY_ATTACK,

  E_ENTRY_CANCEL
};


class MenuEntry
{
public:
  /** \brief Constructor
   */
  // TODO use this one (auto label completion, using a DB)
  explicit MenuEntry(e_entry &entry);

  /** \brief Constructor
   ** \deprecated use MenuEntry(e_entries entry); with auto label completion
   */
  MenuEntry(std::string label_name, e_entry entry);

  /** \brief returns entry Identifier, as a e_entries value
   */
  inline e_entry id() { return _id; }

  /** \brief displays the entry at position
   ** \param position where the entry will be display
   */
  void draw(sf::Vector2f position);

  /** \brief Executes the action matching the entry
   */
  void execute();


private:
  Image _background; ///< background image
  std::shared_ptr<sf::Text> _label; ///< button label text
  Font _font; ///< button label font
  e_entry _id; ///< entry identifier
};

#endif /* !MENUENTRY_HH_ */
