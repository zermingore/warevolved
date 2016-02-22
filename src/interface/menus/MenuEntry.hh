#ifndef MENUENTRY_HH_
# define MENUENTRY_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>


 /// \todo add execute method given to ctor

/**
   * \brief entries descriptors
 */
enum class entry
{
  NONE = 0, // invalid selected entry

  MOVE, // motion order
  STOP, // motion order
  NEXT_TURN,
  ATTACK,

  CANCEL
};


class MenuEntry
{
public:
  /**
   * \brief Constructor
   */
   /// \todo use this one (auto label completion, using a DB)
  explicit MenuEntry(entry &entry);

  /**
   * \brief Constructor
   * \deprecated use MenuEntry(entries entry); with auto label completion
   */
  MenuEntry(std::string label_name, entry entry);

  /**
   * \brief returns entry Identifier, as a entries value
   */
  entry id() { return _id; }

  /**
   * \brief displays the entry at position
   * \param position where the entry will be display
   */
  void draw(Coords position);

  /**
   * \brief Executes the action matching the entry
   */
  void execute();


private:
  entry _id; ///< entry identifier
  std::string _background; ///< background image name
  std::shared_ptr<sf::Text> _label; ///< button label text
  std::string _labelName; ///< menu entry text
  Font _font; ///< button label font
};

#endif /* !MENUENTRY_HH_ */
