#ifndef MENUENTRY_HH_
# define MENUENTRY_HH_

# include <common/include.hh>
# include <resources/Image.hh>
# include <resources/Font.hh>


/** \brief entries descriptors
 */
enum e_entries
{
  E_ENTRIES_NONE = 0, // invalid selected entry

  E_ENTRIES_MOVE, // motion order
  E_ENTRIES_NEXT_TURN,

  E_ENTRIES_VOID1, // TODO remove
  E_ENTRIES_VOID2, // TODO remove

  E_ENTRIES_ATTACK
};


class MenuEntry
{
public:
  /** \brief default Constructor
   */
  MenuEntry();

  /** \brief Constructor
   */
  // TODO use this one (auto label completion, using a DB)
  explicit MenuEntry(e_entries entry);

  /** \brief Constructor
   */
  MenuEntry(std::string label_name, e_entries entry);

  /** \brief Destructor
   */
  ~MenuEntry();


  e_entries getId();

  /** \brief displays the entry at position
   ** \param position where the entry will be display
   */
  void draw(sf::Vector2f position);


  /** \brief Executes the action matching the entry
     */
  void execute();


private:
  Image *_background; ///< background image
  sf::Text* _label; ///< button label text
  Font *_font; ///< button label font
  e_entries _id; ///< entry identifier
};

#endif /* !MENUENTRY_HH_ */
